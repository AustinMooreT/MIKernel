#ifndef TUPLE_H
#define TUPLE_H

namespace std {

  using size_t = unsigned long long int;

  template<class... types>
  class tuple {

    constexpr tuple& (operator=) (const tuple& other);
    constexpr tuple& (operator=) (tuple&& other);
    template<class... utypes>
    constexpr tuple& (operator=) (const tuple<utypes...>& other);
    template<class... utypes>
    constexpr tuple& (operator=) (tuple<utypes...>&& other);

    //TODO implement pair first.
    //template<class t1, class t2>
    //constexpr tuple& (operator=) (const pair<t1,t2>& p);
    //template <class t1,class t2>
    //constexpr tuple& (operator=) (pair<t1,t2>&& p);


  };

  template<std::size_t i, class type>
  struct tuple_element;

  template<std::size_t i, class head, class... tail >
  struct tuple_element<i, std::tuple<head, tail...>>
    : std::tuple_element<i-1, std::tuple<tail...>> { };

  template<class head, class... tail>
  struct tuple_element<0, std::tuple<head, tail...>> {
    typedef head type;
  };

  template<class... u1types, class... u2types>
  constexpr bool (operator==) (const std::tuple<u1types...>& lhs,
                               const std::tuple<u2types...>& rhs);
  template<class... u1types, class... u2types>
  constexpr (operator<=>) (const std::tuple<u1types...>& lhs,
                           const std::tuple<u2types...>& rhs );

  template<std::size_t i, class... types>
  constexpr typename std::tuple_element<i, tuple<types...>>::type& get(tuple<types...>& t) noexcept;

  template<std::size_t i, class... types>
  constexpr typename std::tuple_element<i, tuple<types...>>::type&& get(tuple<types...>&& t) noexcept;

};

#endif //TUPLE_H
