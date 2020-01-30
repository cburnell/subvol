import numpy as np

def trilin_block(single_block, x_samples, y_samples, z_samples):
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

    return np.array(output_block)
def split_into_blocks(s, x_samples = 1, y_samples = 1, z_samples = 1):
    x,y,z = s.shape
    initialized_stuff = [[[0.0 for i in range(x+(x-1)*x_samples)] for j in range(y+(y-1)*y_samples)]for k in range(z+(z-1)*z_samples)]
    initialized_stuff = np.array(initialized_stuff)
    for i in range(x-1):
        for j in range(y-1):
            for k in range(z-1):
                block = s[i:i+2,j:j+2,k:+k+2]
                new_block = trilin_block(block, x_samples, y_samples, z_samples)
                x2,y2,z2 = new_block.shape
                for i2 in range(x2):
                    for j2 in range(y2):
                        for k2 in range(z2):
                            print([[i*(x_samples+1)+i2],[j*(y_samples+1)+j2],[k*(z_samples+1)+k2]])
                            initialized_stuff[i*(x_samples+1)+i2][j*(y_samples+1)+j2][k*(z_samples+1)+k2] = new_block[i2,j2,k2]
    print(initialized_stuff)
test_thing = [[[1,2],[3,4]],[[5,6],[7,8]]]
test_1 = np.array(test_thing)
test_thing = [[[0,0],[0,0]],[[1,1],[1,1]]]
test_2 = np.array(test_thing)
test_thing = [[[0,0,0],[0,0,0],[0,0,0]],[[1,1,1],[1,1,1],[1,1,1]],[[2,2,2],[2,2,2],[2,2,2]]]
test_3 = np.array(test_thing)

split_into_blocks(test_3)
