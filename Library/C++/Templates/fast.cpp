#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("Ofast")

using i64 = int64_t;

namespace fast_input {
	const int buffer_size = 1 << 15;
	char input_buffer[buffer_size];
	int input_position, input_length;

	char read_char() {
		if (input_position == input_length) {
			input_position = 0;
			input_length = (int)fread(input_buffer, 1, buffer_size, stdin);
			if (!input_length) {
				return EOF;
			}
		}
		return input_buffer[input_position++];
	}

	void read_string(string& s) {
		char c;
		while (isspace(c = read_char()));
		do {
			s += c;
		} while (!isspace(c = read_char()) && c != EOF);
	}

	template <class T>
	void read_number(T& n) {
		char c;
		int sign = 1;
		while (!isdigit(c = read_char())) {
			if (c == '-') {
				sign = -1;
			}
		}
		n = c - '0';
		while (isdigit(c = read_char())) {
			n = 10 * n + (c - '0');
		}
		n *= sign;
	}

	template <class T, class... Ts>
	void read_number(T& n, Ts&... ns) {
		read_number(n), read_number(ns...);
	}
}

namespace fast_output {
	const int buffer_size = 1 << 15;
	char output_buffer[buffer_size], number_buffer[100];
	int output_position;

	void flush() {
		fwrite(output_buffer, 1, output_position, stdout);
		output_position = 0;
	}

	void print_char(char c) {
		if (output_position == buffer_size) {
			flush();
		}
		output_buffer[output_position++] = c;
	}

	void print_string(const string& s) {
		for (auto& c : s) {
			print_char(c);
		}
	}

	template <class T>
	void print_number(T n, char after = '\0') {
		if (n < 0) {
			print_char('-'), n *= -1;
		}
		int length = 0;
		for (; n >= 10; n /= 10) {
			number_buffer[length++] = (char)('0' + (n % 10));
		}
		print_char((char)('0' + n));
		for (int i = length - 1; i >= 0; --i) {
			print_char(number_buffer[i]);
		}
		if (after) {
			print_char(after);
		}
	}

	void initialize() {
		assert(atexit(flush) == 0);
	}
}

// start of solution

int main() {
	using namespace fast_input;
	using namespace fast_output;
	initialize();
	
}

// end of solution