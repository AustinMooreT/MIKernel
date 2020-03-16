#include "../../inc/tools/tuple.h"

template<class... types>
constexpr std::tuple<types...>::tuple() {

}

template<std::size_t i, class... types>
constexpr typename std::tuple_element<i, std::tuple<types...>>::type&
  std::get(std::tuple<types...>& t) noexcept {
}
