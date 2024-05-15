#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.10/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAddNode)
		{
			TreeNode* root = nullptr;
			addNode(root, 5);
			addNode(root, 3);
			addNode(root, 8);

			Assert::IsTrue(root != nullptr);
			Assert::IsTrue(root->data == 5);
			Assert::IsTrue(root->left != nullptr);
			Assert::IsTrue(root->left->data == 3);
			Assert::IsTrue(root->right != nullptr);
			Assert::IsTrue(root->right->data == 8);
		}

		TEST_METHOD(TestDeleteNodesInRange)
		{
			TreeNode* root = nullptr;
			addNode(root, 5);
			addNode(root, 3);
			addNode(root, 8);

			deleteNodesInRange(root, 3, 5);
			Assert::IsTrue(search(root, 3) == false);
			Assert::IsTrue(search(root, 5) == false);

			Assert::IsTrue(search(root, 8) == true);
		}

		TEST_METHOD(TestSearch)
		{
			TreeNode* root = nullptr;
			addNode(root, 5);
			addNode(root, 3);
			addNode(root, 8);

			Assert::IsTrue(search(root, 5));
			Assert::IsTrue(search(root, 3));
			Assert::IsTrue(search(root, 8));
			Assert::IsFalse(search(root, 2));
		}
    };
}
