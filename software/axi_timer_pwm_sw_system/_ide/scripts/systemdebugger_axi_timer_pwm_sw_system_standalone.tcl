# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm_sw_system/_ide/scripts/systemdebugger_axi_timer_pwm_sw_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm_sw_system/_ide/scripts/systemdebugger_axi_timer_pwm_sw_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351B7A823A" && level==0 && jtag_device_ctx=="jsn-Zybo Z7-210351B7A823A-13722093-0"}
fpga -file /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm_sw/_ide/bitstream/subsystem_db_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm/export/axi_timer_pwm/hw/subsystem_db_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm_sw/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow /home/mg/Documents/sk8_drone/xilinx_test_projects/axi_timer_pwm/software/axi_timer_pwm_sw/Debug/axi_timer_pwm_sw.elf
configparams force-mem-access 0
bpadd -addr &main
