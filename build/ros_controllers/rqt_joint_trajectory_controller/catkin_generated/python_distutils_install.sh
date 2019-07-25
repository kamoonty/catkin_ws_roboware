#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/kanin/catkin_ws_roboware/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/kanin/catkin_ws_roboware/install/lib/python2.7/dist-packages:/home/kanin/catkin_ws_roboware/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/kanin/catkin_ws_roboware/build" \
    "/usr/bin/python" \
    "/home/kanin/catkin_ws_roboware/src/ros_controllers/rqt_joint_trajectory_controller/setup.py" \
    build --build-base "/home/kanin/catkin_ws_roboware/build/ros_controllers/rqt_joint_trajectory_controller" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/kanin/catkin_ws_roboware/install" --install-scripts="/home/kanin/catkin_ws_roboware/install/bin"
