# CMake generated Testfile for 
# Source directory: /home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller
# Build directory: /home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_four_wheel_steering_controller_rostest_test_four_wheel_steering_controller_twist_cmd.test "/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/test_results/four_wheel_steering_controller/rostest-test_four_wheel_steering_controller_twist_cmd.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller --package=four_wheel_steering_controller --results-filename test_four_wheel_steering_controller_twist_cmd.xml --results-base-dir \"/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/test_results\" /home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller/test/four_wheel_steering_controller_twist_cmd.test ")
add_test(_ctest_four_wheel_steering_controller_rostest_test_four_wheel_steering_controller_4ws_cmd.test "/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/test_results/four_wheel_steering_controller/rostest-test_four_wheel_steering_controller_4ws_cmd.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller --package=four_wheel_steering_controller --results-filename test_four_wheel_steering_controller_4ws_cmd.xml --results-base-dir \"/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/test_results\" /home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller/test/four_wheel_steering_controller_4ws_cmd.test ")
add_test(_ctest_four_wheel_steering_controller_rostest_test_four_wheel_steering_wrong_config.test "/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/test_results/four_wheel_steering_controller/rostest-test_four_wheel_steering_wrong_config.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller --package=four_wheel_steering_controller --results-filename test_four_wheel_steering_wrong_config.xml --results-base-dir \"/home/kanin/catkin_ws_roboware/build_isolated/four_wheel_steering_controller/test_results\" /home/kanin/catkin_ws_roboware/src/ros_controllers/four_wheel_steering_controller/test/four_wheel_steering_wrong_config.test ")
subdirs("gtest")