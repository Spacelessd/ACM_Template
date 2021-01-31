:loop
	mkd.exe
	radix_heap.exe
	dijkstra+priority_queue.exe
	fc 1.out 2.out
	if errorlevel==1 pause
goto loop


