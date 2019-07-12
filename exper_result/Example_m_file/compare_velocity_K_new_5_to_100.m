clear
pkg load io
x1=xlsread('/home/kanin/ROSbag/testK=5C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
x2=xlsread('/home/kanin/ROSbag/testK=10C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
x3=xlsread('/home/kanin/ROSbag/testK=15C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
x4=xlsread('/home/kanin/ROSbag/testK=25C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
x5=xlsread('/home/kanin/ROSbag/testK=50C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
x6=xlsread('/home/kanin/ROSbag/testK=75C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
x7=xlsread('/home/kanin/ROSbag/testK=100C=0/_slash_amr_0_slash_cmd_vel.csv','C2:C510');
%x1=x1(:,1);
period=100;  % in Hz
data_size=size(x1);
data_size=data_size(1,1);
end_t=(1/period)*(data_size-1);
time=0:1/period:end_t;
time=time';

plot(time,x1,'b')
hold on
plot(time,x2,'r')
hold on
plot(time,x3,'g')
hold on
plot(time,x4,'y')
hold on
plot(time,x5,'m')
hold on
plot(time,x6,'k')
hold on
plot(time,x7)
hold on
grid on

title('Line Plot of Velocity for Follower Robot 1 with Time')
xlabel('Time(s)') 
ylabel('Velocity (m/s)') 
set(gca, "linewidth", 2, "fontsize", 15)
h = legend ("K5", "K10", "K15", "K25", "K50","K75","K100");
legend (h, "location", "northeastoutside");
set (h, "fontsize", 20);