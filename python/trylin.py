import numpy as np

def trilin_block(single_block):
    x_len = len(single_block)
    y_len = len(single_block[0])
    z_len = len(single_block[0][0])
    c000 = single_block[0][0][0]
    c100 = single_block[1][0][0]
    c110 = single_block[1][1][0]
    c010 = single_block[0][1][0]
    c010 = single_block[0][1][0]
    c001 = single_block[0][0][1]
    c011 = single_block[0][1][1]
    c101 = single_block[1][0][1]
    c111 = single_block[1][1][1]

    output_x_size = x_len + x_samples
    output_y_size = y_len + y_samples
    output_z_size = z_len + z_samples

    output_block = [[[0 for i in range(output_x_size)] for j in range(output_y_size)] for k in range(output_z_size)]
    for i in range(output_x_size):
        for j in range(output_y_size):
            for k in range(output_z_size):
                xd = i / (output_x_size-1)
                yd = j / (output_y_size-1)
                zd = k / (output_z_size -1)
                c00 = c000*(1-xd)+c100*xd
                c01 = c001*(1-xd)+c101*xd
                c10 = c010*(1-xd)+c110*xd
                c11 = c011*(1-xd)+c111*xd
                c0 = c00*(1-yd)+c10*yd
                c1 = c01*(1-yd)+c11*yd
                c = c0*(1-zd)+c1*zd
                output_block[i][j][k] = c

    print(output_block)
    return output_block

def split_to_blocks(s, x_samples = 1, y_samples = 1, z_samples = 1):
    x_len = len(s)
    y_len = len(s[0])
    z_len = len(s[0][0])
    for i in range(xlen-1):
        for j in range(ylen-1):
            for k in range(zlen-1):
                c000 = s[i][j][k]
                c100 = s[i+1][j][k]
                c010 = s[i][j+1][k]
                c110 = s[i+1][j+1][k]
                c001 = s[i][j][k+1]
                c101 = s[i+1][j][k+1]
                c011 = s[i][j+1][k+1]
                c111 = s[i+1][j+1][k+1]
                next_block = [[c000,c100],[c010,c110],[c001,c101],[c011,c111]]
                expanded_block = trilin_block(next_block, x_samples, y_samples, z_samples)


test_thing = [[[1,2],[3,4]],[[5,6],[7,8]]]
test_thing = [[[0,0],[0,0]],[[1,1],[1,1]]]
test_thing = [[[0,0,0],[0,0,0],[0,0,0]],[[1,1,1],[1,1,1],[1,1,1]],[[2,2,2],[2,2,2],[2,2,2]]]
print(trilin_block(test_thing, 2,2,2))
