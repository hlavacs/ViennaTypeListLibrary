
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

using VeComponentPtr = vtll::variant_type<vtll::to_ptr<VeComponentTypeList>>;


template <typename... Ts>
struct VeEntityType {};

using VeEntityNode = VeEntityType<VeComponentPosition, VeComponentOrientation>;
using VeEntityDraw = VeEntityType<VeComponentMaterial, VeComponentGeometry>;
using VeEntityAnimation = VeEntityType<VeComponentAnimation>;

using VeEntityTypeList = vtll::type_list<
	VeEntityNode
	, VeEntityDraw
	, VeEntityAnimation
	// ,... 
>;

template<typename E>
struct VeHandle_t {
	uint32_t m_entity_index{};			//the slot of the entity in the entity list
	uint32_t m_generation_counter{};	//generation counter
};

using VeHandle = vtll::variant_type<vtll::transform<VeEntityTypeList, VeHandle_t>>;

template <typename E>
struct VeEntity_t {
	using tuple_type = typename vtll::to_tuple<E>::type;
	VeHandle_t<E>	m_handle;
	tuple_type		m_component_data;

	VeEntity_t(const VeHandle_t<E>& h, const tuple_type& tup) noexcept : m_handle{ h }, m_component_data{ tup } {};

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
};

using VeEntity = vtll::variant_type<vtll::transform<VeEntityTypeList, VeEntity_t>>;
using VeEntityPtr = vtll::variant_type<vtll::to_ptr<vtll::transform<VeEntityTypeList, VeEntity_t>>>;

//...

int main() {
	vtll::detail::f();

	return 0;
}

