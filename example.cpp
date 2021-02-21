
#include <vector>
#include <optional>
#include "VTLL.h"


//the following examples are lifted and adapted from the Vienna Entity Component System (VECS)

struct VeComponentPosition {
	float x,y,z;
};

struct VeComponentOrientation {
	float i,j,k, r;
};

struct VeComponentMaterial {
	int idx;
};

struct VeComponentGeometry {
	int idx;
};

struct VeComponentAnimation {
	std::vector<float> t;
	std::vector<float> y;

};

using VeComponentTypeList = vtll::type_list<
	VeComponentPosition
	, VeComponentOrientation
	, VeComponentMaterial
	, VeComponentGeometry
	, VeComponentAnimation
	//, ...
>;

using VeComponentPtr = vtll::to_variant<vtll::to_ptr<VeComponentTypeList>>;


template <typename... Ts>
struct VeEntityType {};

using VeEntityNode = VeEntityType<VeComponentPosition, VeComponentOrientation>;
using VeEntityDraw = VeEntityType<VeComponentMaterial, VeComponentGeometry>;
using VeEntityAnimation = VeEntityType<VeComponentAnimation>;

using VecsEntityTypeList = vtll::type_list<
	VeEntityNode
	, VeEntityDraw
	, VeEntityAnimation
	// ,... 
>;

struct VecsHandle {
	uint32_t m_entity_index{};			//the slot of the entity in the entity list
	uint16_t m_generation_counter{};	//generation counter
	uint16_t m_index{};					//type index
	uint32_t index() const { return static_cast<uint32_t>(m_index); };
	//....
};


template <typename E>
struct VecsEntity {
	using tuple_type = vtll::to_tuple<E>;
	VecsHandle	m_handle;
	tuple_type	m_component_data;

	VecsEntity(const VecsHandle& h, const tuple_type& tup) noexcept : m_handle{ h }, m_component_data{ tup } {};

	template<typename C>
	std::optional<C> component() noexcept {
		if constexpr (vtll::has_type<E, C>::value) {
			return { std::get<vtll::index_of<E,C>::value>(m_component_data) };
		}
		return {};
	};

	template<typename C>
	void update(C&& comp) noexcept {
		if constexpr (vtll::has_type<E, C>::value) {
			std::get<vtll::index_of<E, C>::value>(m_component_data) = comp;
		}
		return;
	};

	//....
};


//...

int main() {
	vtll::detail::f();

	return 0;
}

