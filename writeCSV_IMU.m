% This is a Matlab function which establishes connection 
% to the COM port it then reads values from the comport and 
% creates a CSV file with the values that it reads. 
% The values here will need to be changed depending on what 
% computer you are on. Specifically the comPort and the USB 
% connection Parameters.

comPort = 'COM9';
s = serial(comPort);
set(s, 'DataBits', 8);
set(s, 'StopBits', 1);
set(s, 'BaudRate', 115200);
set(s, 'Parity', 'none');
fopen(s);
fgets(s);

    while(true)
        data = fscanf(s, '%f %f %f %f %f %f %f %f %f %f');
        data_reshape = reshape(data,1,10);
        dlmwrite('IMUdata.csv', data_reshape, '-append');
        disp(data_reshape);
    end