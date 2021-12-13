// Copyright 2021 Mustafa Moiz.

#pragma once

#include <utility>

class NoOne {};

/**
 * Represents a value that is readonly to the general public.
 * It can be written to by a single class, specified at compile time,
 * which makes it a good candidate for use with Builder or other
 * constructor-style classes.
 */
template<typename Type, typename Writer = NoOne>
class Value
{
public:

	Value() = default;
	explicit Value(Type value): value_(std::move(value)) {}
	const Type& operator()() const { return value_; }
	operator const Type&() const { return value_; }
	
private:

	Type& operator*() { return value_; }
	
	Type value_;
	friend Writer;
};
