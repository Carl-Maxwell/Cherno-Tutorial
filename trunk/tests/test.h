#pragma once

#include <vector>
#include <string>
#include <functional>
#include <utility>

#include "print.h"

namespace test{

class Test{
public:
  std::string title;

  Test() {}
  virtual ~Test() {}

  virtual void onUpdate(float delta_time) {}
  virtual void onRender() {}
  virtual void onImguiRender() {}
};

class TestMenu : public Test{
private:
  std::vector< std::pair< std::string, std::function< Test*() >>> m_tests;
  Test*& m_current_test;
public:
  TestMenu(Test*& current_test_ptr);
  // ~TestMenu();

  void onImguiRender() override;
  
  template <class T>
  void registerTest(const std::string& name) {
    Print::line("Registering test " + name);
    m_tests.push_back(std::make_pair(name, [name](){
      T* new_test = new T(); 
      new_test->title = name;
      Print::line("Lambda registering " + name + " = " + new_test->title);
      return new_test;
    }));
  }

};

}