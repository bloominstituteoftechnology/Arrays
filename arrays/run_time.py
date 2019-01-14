import time

start_time = time.time()
add_to_back = (500000) #0(n) 600x faster than add_to_front
end_time = time.time()
print (f"runtime: {end_time -start_time}seconds")

start_time = time.time()
add_to_front = (500000) #0(n^2)
end_time = time.time()
print (f"runtime: {end_time -start_time}seconds")

