#include<iostream>
#include<string>
#include<memory>
#include<stack>

class Node {
public:
	virtual int Evaluate()const = 0;
};

class Value :public Node {
private:
	const uint8_t _val;
public:
	Value(const char& c) :_val(c - '0') {}

	int Evaluate()const override { return _val; }
};

class Variable :public Node {
private:
	const int8_t& _x;
public:
	Variable(const int& x) :_x(x) {}

	int Evaluate()const override { return _x; }
};

class Operators :public Node {
private:
	std::shared_ptr<Node> _left, _right;
	char _op;
public:
	Operators(const char c) : _precedance([c] {
		return (c == '*') ? 2 : 1; }())
		, _op(c) {}

		int Evaluate()const override {
			if (_op == '-') {
				return _left->Evaluate() - _right->Evaluate();
			}
			else if (_op == '+') {
				return _left->Evaluate() + _right->Evaluate();
			}
			else if (_op == '*') {
				return _left->Evaluate() * _right->Evaluate();
			}
			return 0;
		}

		void SetLeft(const std::shared_ptr<Node>& left) {
			_left = left;
		}

		void SetRight(const std::shared_ptr<Node>& right) {
			_right = right;
		}
		const uint8_t _precedance;
};

template<typename Item>
std::shared_ptr<Node> Parse(Item&& it_begin, Item&& it_end, const int& x) {
	if (it_begin == it_end)return nullptr;

	auto current_item = it_begin;
	std::stack<std::shared_ptr<Node>> values;
	std::stack<std::shared_ptr<Operators>> operators;

	auto PopTop = [&](int precedence) {
		while (!operators.empty() && operators.top()->_precedance >= precedence) {
			auto val1 = values.top();
			values.pop();
			auto val2 = values.top();
			values.pop();
			auto op = operators.top();
			operators.pop();

			op->SetLeft(val2);
			op->SetRight(val1);

			values.push(op);
		}
	};

	while (current_item != it_end) {
		if ((*current_item >= '0') && (*current_item <= '9')) {
			values.push(std::make_shared<Value>(*current_item));
		}
		else if (*current_item == 'x') {
			values.push(std::make_shared<Variable>(x));
		}
		else if ((*current_item == '+') || (*current_item == '-')) {
			PopTop(1);
			operators.push(std::make_shared<Operators>(*current_item));
		}
		else if (*current_item == '*') {
			PopTop(2);
			operators.push(std::make_shared<Operators>(*current_item));
		}
		current_item++;

	}

	if (!operators.empty()) {
		PopTop(0);
	}

	return values.top();
}

int main() {
	std::string expr{};
	int x;

	std::cout << "Enter your expresion: ";
	std::cin >> expr;
	auto op = Parse(expr.begin(), expr.end(), x);

	std::cout << "Enter mean value x: ";
	std::cin >> x;
	std::cout << "The resault: " << op->Evaluate();

	return 0;
}
