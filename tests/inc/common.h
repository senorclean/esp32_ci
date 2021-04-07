// Copyright 2021 <Some Dude>

#pragma once

// when using enum classes, gtest needs to have the "<<" operator defined to understand
// how to print them. this is an example showing how you would do this with an enum named State

// namespace gpio {
// std::ostream& operator<<(std::ostream& os, const State& val) {
//   return os << static_cast<std::underlying_type<State>::type>(val);
// }
// };
