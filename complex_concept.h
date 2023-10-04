#pragma once
#include <iostream>
#include <sstream>
#include <concepts>

namespace avhw34
{
	template <typename T>
	concept HasHashMethod = requires(const T v) { {v.hash()}->std::convertible_to<long>; };

	template <typename T>
	concept HasToStringMethod = requires(const T v) { {v.toString()}->std::same_as<std::string>; };

	template <typename T>
	concept AbsentVirtualDestructor = !std::has_virtual_destructor<T>::value;

	template <typename T>
	concept ComplexConcept = HasHashMethod<T> && HasToStringMethod<T> && AbsentVirtualDestructor<T>;

	template <ComplexConcept T>
	std::stringstream typeTest(const T& v)
	{
		std::stringstream result;
		try
		{
			v.toString();
			result << "Type is OK";
		}
		catch (const std::exception& e)
		{
			result << "Type is not acceptable: " << e.what();
		}
		return result;
	}

	class TestClass
	{
	public:
		TestClass() {};
		~TestClass() {};
		int hash() const;
		std::string toString() const;
	};

	int TestClass::hash() const { return 0; }
	std::string TestClass::toString() const { return "This is TestClass"; }
}