

/**
 * TODO: Complete these class definitions
 */

/// Starter includes (YW)
#include "MyDetector.hpp"
#include "MyStack.hpp"
#include "MyQueue.hpp"

//
namespace CPSC131::PalindromeDetector
{
	/// YOUR WELCOME
	MyDetector::MyDetector() {}
	
	//
	bool MyDetector::isPalindrome(std::string s) {
		queue.clear();
		stack.clear();

		for (size_t i = 0; i < s.size(); ++i) {
			char c = s[i];
			if (c >= 'A' && c <= 'Z') {
				c += 'a' - 'A'; // Convert to lowercase
			}

			if (c >= 'a' && c <= 'z') {
				queue.enqueue(c);
				stack.push(c);
			}
		}

		while (!queue.empty())
		{
			if (queue.front() != stack.top()) {
				return false;
			}
			queue.dequeue();
			stack.pop();
		}

		return true;
	}
}












