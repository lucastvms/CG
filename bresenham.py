"""
x   Y   d   choosen pixels  increment
1   1   1         NE          1+(-2) = -1
2   2   -1        E          -1+4 = 3
3   2   3         NE          3+(-2) = 1
4   3   1         NE          1+(-2) = -1
"""

def line_bresenham(x1, y1, x2, y2, color):
  # starting values
  dx = x2 - x1
  dy = y2 - y1
  d = 2*dy-dx
  incE = 2*dy
  incNE = 2*(dy-dx)
  x = x1
  y = y1
  choice = "NE" if d>0 else "E" 
  print(x, y, d, choice, color)  #write_pixel(x, y, color)

  while x < x2:
    if d<=0:
      # escolhe E
      d = d+incE
      x = x+1
    else:
      # escolhe NE
      d = d+incNE
      x = x+1
      y = y+1

    choice = "NE" if d>0 else "E" 
    print(x, y, d, choice, color)  #write_pixel(x, y, color)


"""
x   Y   d   choosen pixels  increment
1   1   1         NE          1+(-2) = -1
2   2   -1        E          -1+4 = 3
3   2   3         NE          3+(-2) = 1
4   3   1         NE          1+(-2) = -1
"""
def circle_bresenham(r, color):
  #starting values 2nd octant
  x = 0
  y = r
  d = 5/4 - r

  choice = "E" if d<0 else "SE" 
  print(x, y, d, choice, color)  #write_pixel(x, y, color)

  while(y > x):
    if d<0:
      #  escolhe E
      d = d+2*x+3
      ++x
    else:
      #  escolhe SE
      d = d+2*(x-y)+5
      ++x
      --y

  choice = "E" if d<0 else "SE" 
  print(x, y, d, choice, color)  #write_pixel(x, y, color)
    

line_bresenham(1, 1, 4, 3, "black")

circle_bresenham(1, "black")
