
delete(instrfindall) 
esduino = serial('COM3','BaudRate',9600,'Terminator','CR'); %the esduino uses the com port #4 on my desktop--might need changing on laptop
fopen(esduino);

signal = animatedline('color','r'); 
title('Measured Angle over Time')
xlabel('time (seconds)'); 
ylabel('Angle (degrees)');
time = 0; % initialize time to zero (of course) 

while(1)
    % Infinite loop because we will continually poll. 
    angle = str2num(fgetl(esduino)); 
    addpoints(signal,time, angle); 
    drawnow; 
    time = time + 1; % Continuously increment time to move forward
end


