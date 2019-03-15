set project_name sdk_led
set part_name xc7z010clg400-1
set ip_dir repo
set bd_name system
set bd_path $project_name/$project_name.srcs/sources_1/bd/$bd_name

file delete -force $project_name

create_project -part $part_name $project_name $project_name

set_property board_part digilentinc.com:zybo-z7-10:part0:1.0 [current_project]

set_property ip_repo_paths $ip_dir [current_project]
update_ip_catalog

create_bd_design $bd_name

create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0

apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]

create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_0

set_property CONFIG.USE_BOARD_FLOW true [get_bd_cells /axi_gpio_0]
set_property CONFIG.GPIO_BOARD_INTERFACE Custom [get_bd_cells /axi_gpio_0]
create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 gpio_rtl
connect_bd_intf_net /gpio_rtl /axi_gpio_0/GPIO

apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/processing_system7_0/M_AXI_GP0} Slave {/axi_gpio_0/S_AXI} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins axi_gpio_0/S_AXI]

regenerate_bd_layout

set_property -dict [list CONFIG.C_GPIO_WIDTH {1}] [get_bd_cells axi_gpio_0]

file mkdir /media/wrg/evo_860/stream_fpga/workspace/sdk_led/sdk_led.srcs/constrs_1
file mkdir /media/wrg/evo_860/stream_fpga/workspace/sdk_led/sdk_led.srcs/constrs_1/new
close [ open /media/wrg/evo_860/stream_fpga/workspace/sdk_led/sdk_led.srcs/constrs_1/new/zybo_z7_10.xdc w ]
add_files -fileset constrs_1 /media/wrg/evo_860/stream_fpga/workspace/sdk_led/sdk_led.srcs/constrs_1/new/zybo_z7_10.xdc


