clear
pkg load io
x_vl=xlsread('_slash_vl_robot_slash_cmd_vel.csv','C2:C11700');
y_vl=xlsread('_slash_vl_robot_slash_cmd_vel.csv','D2:D11700');
x1=xlsread('_slash_amr_0_slash_cmd_vel.csv','C2:C11700');
y1=xlsread('_slash_amr_0_slash_cmd_vel.csv','D2:D11700');
x2=xlsread('_slash_amr_1_slash_cmd_vel.csv','C2:C11700');
y2=xlsread('_slash_amr_1_slash_cmd_vel.csv','D2:D11700');
x3=xlsread('_slash_amr_2_slash_cmd_vel.csv','C2:C11700');
y3=xlsread('_slash_amr_2_slash_cmd_vel.csv','D2:D11700');
x4=xlsread('_slash_amr_3_slash_cmd_vel.csv','C2:C11700');
y4=xlsread('_slash_amr_3_slash_cmd_vel.csv','D2:D11700');
%x1=x1(:,1);
period=100;  % in Hz
data_size=size(x1);
data_size=data_size(1,1);
end_t=(1/period)*(data_size-1);
time=0:1/period:end_t;
time=time';

plot(time,x1,'b')
hold on
%plot(time,x_vl,'*')
%hold on
plot(time,x2,'g')
hold on
plot(time,x3,'m')
hold on
plot(time,x4,'r')
hold on
grid on

title('Robot Path')
xlabel('X Distance (m)') 
ylabel('Y Distance (m)') 
set(gca, "linewidth", 2, "fontsize", 15)
h = legend ("Robot 1", "Virtual robot", "Robot 2","Robot 3","Robot 4" );
legend (h, "location", "northeastoutside");
set (h, "fontsize", 20);