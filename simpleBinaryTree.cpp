#include<iostream>
#include<memory>


template<typename T>
class BinaryTree {
private:
	
	struct Node {
		T data;

		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;


		template<typename P>
		Node(P&& val) {
			if constexpr (std::is_rvalue_reference_v<decltype(val)>) {
				data = std::move(val);
			}
			else {
				data = val;
			}
		}
	};

	 std::shared_ptr<Node> rootTree = nullptr;

public:

	BinaryTree() = default;

	template<typename P>
	BinaryTree(P&& val) {
		this->rootTree = std::make_shared<Node>(Node(std::forward<decltype(val)>(val)));
	}

	template<typename P>
	void AddNode(P&& val) {
		std::shared_ptr<Node> currentNode = rootTree;
		for (;;) {
			if (currentNode->data > val) {
				if (currentNode->left == nullptr) {
					currentNode->left=std::make_shared<Node>(Node(std::forward<decltype(val)>(val)));
					break;
				}
				currentNode = currentNode->left;
			}
			else
			{
				if (currentNode->right == nullptr) {
					currentNode->right=std::make_shared<Node>(Node(std::forward<decltype(val)>(val)));
					break;
				}
				currentNode = currentNode->right;
			}
		}
	}

	T findElement(T val) {
		std::shared_ptr<Node> currentNode = rootTree;
		while(currentNode->data!=val) {
			if (currentNode->data > val) {
				if (currentNode->left == nullptr) {
					return INT_MIN;
				}
				currentNode = currentNode->left;
			}
			else
			{
				if (currentNode->right == nullptr) {
					return INT_MIN;
				}
				currentNode = currentNode->right;
			}
		}
		return currentNode->data;
	}

	~BinaryTree() = default;
};

