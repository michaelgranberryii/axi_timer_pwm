# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {axi_timer_pwm}\
-hw {/home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/hardware/export/subsystem_db_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {/home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software}

platform write
platform generate -domains 
platform active {axi_timer_pwm}
platform generate
platform active {axi_timer_pwm}
platform config -updatehw {/home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/hardware/export/subsystem_db_wrapper.xsa}
platform generate -domains 
platform active {axi_timer_pwm}
platform generate -domains 
