#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std;
using std::placeholders::_1;

bool is_prime(int number) {
    if (number == 1) {
        return false; 
    }

    // Check divisibility from 2 up to the square root of the number
    int sqrt_num = sqrt(number);
    for (int i = 2; i <= sqrt_num; ++i) {
        if (number % i == 0) {
            return false; // Found a factor, not a prime
        }
    }

    return true; 
}


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "random_numbers", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::Int32 & msg) 
    {
    int rec_num = msg.data;

    bool is_prime_num = is_prime(rec_num);

    if (is_prime_num) {
      RCLCPP_INFO(this->get_logger(), "%d is a Prime number", rec_num);
    } else {
      RCLCPP_INFO(this->get_logger(), "%d is a Composite number", rec_num);
    }
  }
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
