Setup the mouse device for all users to read

    sudo chmod a+r /dev/input/mice

For the main test application:

    cd build && rm -rf * && cmake .. && make -j7 && make run_test1

For running the mouse hook test app

    cd build && rm -rf * && cmake .. && make -j7 && make mousehook