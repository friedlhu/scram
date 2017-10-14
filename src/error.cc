/*
 * Copyright (C) 2014-2017 Olzhas Rakhimov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/// @file error.cc
/// Implementation of the exceptions for use in SCRAM.

#include "error.h"

#include <boost/exception/get_error_info.hpp>

namespace scram {

Error::Error(std::string msg) : msg_(std::move(msg)) {}

const char* Error::what() const noexcept {
  if (const char* const* msg = boost::get_error_info<error::what>(*this))
    return *msg;
  return msg_.c_str();
}

}  // namespace scram
