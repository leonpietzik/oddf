/*

    ODDF - Open Digital Design Framework
    Copyright Advantest Corporation

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

/*

    <no description>

*/

#include "../SimulatorCore.h"
#include "../SimulatorBlockInternals.h"

#include <oddf/Exception.h>

#include <list>
#include <memory>
#include <cassert>
#include <iostream>
#include <set>

namespace oddf::simulator::common::backend {

namespace {

class ComponentBuilder {

private:

	std::list<SimulatorComponent> &m_components;
	std::list<SimulatorComponent *> m_staleComponents;

	SimulatorComponent *m_currentComponent;

	SimulatorComponent *NewComponent()
	{
		SimulatorComponent *component = nullptr;

		if (!m_staleComponents.empty()) {

			component = m_staleComponents.back();
			m_staleComponents.pop_back();
		}
		else {

			component = &m_components.emplace_back();
		}

		assert(component);
		assert(component->IsEmpty());

		return component;
	}

	void ReleaseComponent(SimulatorComponent *component)
	{
		assert(component);
		assert(component->IsEmpty());

		m_staleComponents.push_back(component);
	}

	auto GetDrivingBlocks(SimulatorBlockBase &block)
	{
		std::set<SimulatorBlockBase *> drivingBlocks;

		auto inputsEnumerator = block.GetInputsList().GetEnumerator();

		for (inputsEnumerator.Reset(); inputsEnumerator.MoveNext();) {

			auto &input = inputsEnumerator.GetCurrent();

			if (input.IsConnected())
				drivingBlocks.insert(&input.GetDriver().GetOwningBlock());
		}

		return drivingBlocks;
	}

	SimulatorBlockBase const *VisitBlock(SimulatorBlockBase &e)
	{
		if (e.m_internals->m_component) {

			assert(!e.m_internals->m_visiting);

			SimulatorComponent *otherComponent = e.m_internals->m_component;

			if (otherComponent != m_currentComponent) {

				// Entities from 'otherComponent' and 'm_currentComponent' must be
				// merged. Since entities from 'otherComponent' had already been
				// visited, they need to be placed before elements from 'm_currentComponent'.

				if (m_currentComponent->GetSize() < otherComponent->GetSize()) {

					otherComponent->MoveAppendFromOther(*m_currentComponent);
					ReleaseComponent(m_currentComponent);
					m_currentComponent = otherComponent;
				}
				else {

					m_currentComponent->MovePrependFromOther(*otherComponent);
					ReleaseComponent(otherComponent);
				}
			}

			return nullptr;
		}

		if (e.m_internals->m_visiting) {

			// Messages::Info("A loop was detected in the execution graph starting at block '%s'...", e->mBlock.GetFullName().c_str());
			std::cout << "INFO: A loop was detected in the execution graph starting at block '" << e.GetDesignPathHint() << "'\n";
			return &e;
		}

		e.m_internals->m_visiting = true;

		auto drivingBlocks = GetDrivingBlocks(e);

		for (auto *drivingBlock : drivingBlocks) {

			auto *loop = VisitBlock(*drivingBlock);
			if (loop) {

				if (loop != &e) {

					std::cout << "INFO: ... going through block '" << e.GetDesignPathHint() << "' ...\n";
					return loop;
				}
				else {

					std::cout << "INFO: ... and returning to block '" << e.GetDesignPathHint() << "' again.\n";
					throw oddf::Exception(oddf::ExceptionCode::Fail);
				}
			}
		}

		e.m_internals->m_visiting = false;

		m_currentComponent->AddBlock(e);
		return nullptr;
	}

public:

	ComponentBuilder(ComponentBuilder const &) = delete;

	ComponentBuilder(std::list<SimulatorComponent> &components) :
		m_components(components),
		m_staleComponents(),
		m_currentComponent()
	{
	}

	void operator=(ComponentBuilder const &) = delete;

	void BuildComponents(std::vector<std::unique_ptr<SimulatorBlockBase>> &blocks)
	{
		for (auto &block : blocks) {

			m_currentComponent = NewComponent();
			assert(block);
			VisitBlock(*block);
		}

		m_components.remove_if([](auto const &component) { return component.IsEmpty(); });
	}
};

} // namespace

void SimulatorCore::BuildComponents()
{
	std::cout << "\n";
	std::cout << "-- Building components --\n";
	std::cout << "\n";

	auto componentBuilder = ComponentBuilder(m_components);
	componentBuilder.BuildComponents(m_blocks);
}

} // namespace oddf::simulator::common::backend
