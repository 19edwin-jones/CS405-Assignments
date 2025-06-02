// Uncomment the next line to use precompiled headers
// #include "pch.h"
// uncomment the next line if you do not use precompiled headers
#include <gtest/gtest.h>
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment {
public:
  ~Environment() override {}

  // Override this to define how to set up the environment.
  void SetUp() override {
    //  initialize random seed
    srand(time(nullptr));
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test {
protected:
  // create a smart point to hold our collection
  std::unique_ptr<std::vector<int>> collection;

  void SetUp() override { // create a new collection to be used in the test
    collection.reset(new std::vector<int>);
  }

  void
  TearDown() override { //  erase all elements in the collection, if any remain
    collection->clear();
    // free the pointer
    collection.reset(nullptr);
  }

  // helper function to add random values from 0 to 99 count times to the
  // collection
  void add_entries(int count) {
    assert(count > 0);
    for (auto i = 0; i < count; ++i)
      collection->push_back(rand() % 100);
  }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for
// the test case. Use EXPECT when failure should notify, but processing should
// continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull) {
  // is the collection created
  ASSERT_TRUE(collection);

  // if empty, the size must be 0
  ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate) {
  // is the collection empty?
  ASSERT_TRUE(collection->empty());

  // if empty, the size must be 0
  ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
// TEST_F(CollectionTest, AlwaysFail)
// {
//   FAIL();
// }

// DONE: Create a test to verify adding a single value to an empty collection ✔︎
TEST_F(CollectionTest, CanAddToEmptyVector) {
  // is the collection empty?
  // if empty, the size must be 0
  EXPECT_TRUE(collection->empty());
  ASSERT_EQ(collection->size(), 0);

  add_entries(1);

  // is the collection still empty?
  // if not empty, what must the size be?
  EXPECT_FALSE(collection->empty());
  ASSERT_EQ(collection->size(), 1);
}

// DONE: Create a test to verify adding five values to collection ✔︎
TEST_F(CollectionTest, CanAddFiveValuesToVector) {
  EXPECT_TRUE(collection->empty());
  add_entries(5);
  ASSERT_EQ(collection->size(), 5);
}

// DONE: Create a test to verify that max size is greater than or equal to size
// for 0, 1, 5, 10 entries ✔︎
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize) {
  ASSERT_TRUE(collection->empty());

  // Check for 0 entries
  ASSERT_EQ(collection->size(), 0);
  ASSERT_GE(collection->max_size(), collection->size());

  // Add 1 entry and check
  add_entries(1);
  ASSERT_EQ(collection->size(), 1);
  ASSERT_GE(collection->max_size(), collection->size());

  // Add 5 entries and check
  add_entries(4);
  ASSERT_EQ(collection->size(), 5);
  ASSERT_GE(collection->max_size(), collection->size());

  // Add 10 entries and check
  add_entries(5);
  ASSERT_EQ(collection->size(), 10);
  ASSERT_GE(collection->max_size(), collection->size());
}

// DONE: Create a test to verify that capacity is greater than or equal to size
// for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize) {
  ASSERT_TRUE(collection->empty());

  // Check for 0 entries
  ASSERT_EQ(collection->size(), 0);
  ASSERT_GE(collection->capacity(), collection->size());

  // Add 1 entry and check
  add_entries(1);
  ASSERT_EQ(collection->size(), 1);
  ASSERT_GE(collection->capacity(), collection->size());

  // Add 4 entries and check
  add_entries(4);
  ASSERT_EQ(collection->size(), 5);
  ASSERT_GE(collection->capacity(), collection->size());

  // Add 5 entries and check
  add_entries(5);
  ASSERT_EQ(collection->size(), 10);
  ASSERT_GE(collection->capacity(), collection->size());
}

// DONE: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection) {
  // Start with an empty collection
  ASSERT_TRUE(collection->empty());
  EXPECT_EQ(collection->size(), 0);

  // Resize to a larger size
  const size_t NEW_SIZE = 10;
  collection->resize(NEW_SIZE);

  // Check that the size has increased
  ASSERT_EQ(collection->size(), NEW_SIZE);
  EXPECT_FALSE(collection->empty());

  // Check that the capacity is still greater than or equal to the size
  ASSERT_GE(collection->capacity(), collection->size());
}

// DONE: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection) {
  // Start with a collection of size 10
  add_entries(10);
  ASSERT_EQ(collection->size(), 10);

  // Resize to a smaller size
  const size_t NEW_SIZE = 5;
  collection->resize(NEW_SIZE);

  // Check that the size has decreased
  ASSERT_EQ(collection->size(), NEW_SIZE);

  // Check that the remaining elements are still valid
  for (size_t i = 0; i < NEW_SIZE; ++i) {
    EXPECT_GE((*collection)[i], 0);
    EXPECT_LT((*collection)[i], 100);
  }
}

// DONE: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeToZero) {
  // Start with a collection of size 10
  add_entries(10);
  EXPECT_EQ(collection->size(), 10);

  // Resize to zero
  collection->resize(0);

  // Check that the size is now zero
  ASSERT_EQ(collection->size(), 0);
  ASSERT_TRUE(collection->empty());
}

// DONE: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) {
  // Add some entries to the collection
  add_entries(5);
  EXPECT_FALSE(collection->empty());
  EXPECT_EQ(collection->size(), 5);

  // Clear the collection
  collection->clear();

  // Check that the collection is now empty
  ASSERT_TRUE(collection->empty());
  ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseRangeErasesCollection) {
  // Add some entries to the collection
  add_entries(5);
  EXPECT_FALSE(collection->empty());
  EXPECT_EQ(collection->size(), 5);

  // Erase the entire range
  collection->erase(collection->begin(), collection->end());

  // Check that the collection is now empty
  ASSERT_TRUE(collection->empty());
  ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify reserve increases the capacity but not the size
// of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacity) {
  // Start with an empty collection
  EXPECT_TRUE(collection->empty());
  EXPECT_EQ(collection->size(), 0);
  EXPECT_GE(collection->capacity(), collection->size());

  // Reserve space for 10 elements
  const size_t RESERVE_SIZE = 10;
  collection->reserve(RESERVE_SIZE);

  // Check that the capacity has increased
  ASSERT_GE(collection->capacity(), RESERVE_SIZE);

  // Check that the size is still zero
  ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify the std::out_of_range exception is thrown when
// calling at() with an index out of bounds NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsOutOfRange) {
  // Start with an empty collection
  EXPECT_TRUE(collection->empty());
  EXPECT_EQ(collection->size(), 0);

  // Attempt to access an element at index 0, which should throw
  // std::out_of_range
  ASSERT_THROW({ collection->at(0); }, std::out_of_range);
}

// DONE: Create 2 unit tests of your own to test something on the collection -
// do 1 positive & 1 negative

// Positive test to verify that swapping contents of two collections works
// correctly
TEST_F(CollectionTest, SwapContents) {
  // Add some entries to the collection
  add_entries(5);
  EXPECT_EQ(collection->size(), 5);
  std::vector<int> collectionOriginal = *collection;

  // Create another collection and add some different entries
  std::vector<int> otherCollection;
  for (int i = 0; i < 5; ++i) {
    otherCollection.push_back(rand() % 100 + 100); // Different range
  }
  std::vector<int> otherCollectionOriginal = otherCollection;

  // Swap contents
  collection->swap(otherCollection);

  // Check that the contents have been swapped
  ASSERT_EQ(*collection, otherCollectionOriginal);
  ASSERT_NE(*collection, collectionOriginal);

  ASSERT_EQ(otherCollection, collectionOriginal);
  ASSERT_NE(otherCollection, otherCollectionOriginal);
}

// Negative test to verify that accessing an out-of-bounds index throws
// std::out_of_range
TEST_F(CollectionTest, AccessOutOfBoundsThrows) {
  // Add some entries to the collection
  add_entries(5);
  EXPECT_EQ(collection->size(), 5);

  // Attempt to access an element at an out-of-bounds index
  ASSERT_THROW(
      {
        collection->at(
            10); // Index 10 is out of bounds for a collection of size 5
      },
      std::out_of_range);
}
