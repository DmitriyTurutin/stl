#pragma once
#include <iostream>
#include <string>
#include <exception>

class Exception : public std::exception {
private:
	std::string error;

public:

	Exception(const std::string& _error, int index) {
		error.assign(_error + " size:  " + std::to_string(index));
	}

	Exception(const std::string& _error) : error(_error) {}

	const char* what() const noexcept override {
		return error.c_str();
	}
};

