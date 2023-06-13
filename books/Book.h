#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <iomanip>
#include "../users/User.h"
#include "../styles/colors.h"

// Forward declaration of the Comment class
class Comment;

class Book
{
public:
  // Default constructor
  Book();

  // Parameterized constructor
  Book(int buid, std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount = 1, bool isCanLend = true);

  // Getter methods for private member variables
  int getBuid() const;            // Get the book ID
  std::string getBName() const;   // Get the book name
  int getBCount() const;          // Get the number of books
  std::string getBSeries() const; // Get the book series
  std::string getBAuthor() const; // Get the author name
  std::string getBPub() const;    // Get the publisher
  std::string getBDate() const;   // Get the publish date
  bool getIsCanLend();            // Get the availability for lending

  // Setter methods for private member variables
  void setBCount(int newBCount);        // Set the number of books available
  void setIsCanLend(bool newIsCanLend); // Set the availability for lending

  // Print the book information
  void BookInfo();

  Comment getComment(); // Declaration of the Comment class

private:
  int buid;               // Book ID
  std::string bookName;   // Book name
  std::string bookSeries; // Book series
  int bookCount;          // Number of copies available
  std::string bookDate;   // Publish date
  std::string bookAuthor; // Author name
  std::string bookPub;    // Publisher
  bool isCanLend;         // Availability for lending
};

#endif
