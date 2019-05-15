from PIL import Image

x_min = -2.0
x_max = 2.0

y_min = -2.0
y_max = 2.0

colors = [\
(220, 30, 50), (30, 220, 50), (30, 50, 220), \
(0, 190, 180), (180, 0, 175), (180, 255, 0)]



def newtons_method(f, f_prime, z):
 
    for i in range(60):

        new_z = z - f(z)/f_prime(z)
            
        if abs(new_z - z) < 10e-4:
            return z
        z = new_z

    return None

def newton_fractal(f, f_prime, img, size):
    roots = []
    for y in range(size):
        z_y = y * (y_max - y_min)/(size - 1) + y_min
        for x in range(size):
            z_x = x * (x_max - x_min)/(size - 1) + x_min
            root = newtons_method(f, f_prime, complex(z_x, z_y))
            if root:
                flag = False
                for test_root in roots:
                    if abs(test_root - root) < 10e-3:
                        root = test_root
                        flag = True
                        break
                if not flag:
                    roots.append(root)
            if root:
                img.putpixel((x, y), colors[roots.index(root)])
    return img
 
size = 1024
img = Image.new("RGB", (size, size), (255, 255, 255))
newton_fractal(lambda z: z * z * z - 1.0, lambda z: 3.0 * (z*z), img, size);
img