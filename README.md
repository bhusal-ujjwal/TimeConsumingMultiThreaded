**Multi-threaded GUI application allowing users to perform various time-consuming calculations. 
Used C++ programming language and Qt GUI toolkit for the implementation.**

**The application has following features:**
At least two active worker threads must be allowed at a time
The activity of the thread/calculation progress must be properly indicated within the application's UI
Display the state of the calculation (running/suspended/stopped)
Use any type of progress bar
Show the running time
Show the estimation of reaming time (the linear approximation is sufficient) 
The user can specify the algorithm input parameters (target factorial number, amount of prime numbers to be calculated, ...)
The worker threads can be suspended/resumed/deleted by a user
If needed, slow down the worker thread by using Sleep() function to allow users to interact with the thread
Allow the threads to work with big numbers (use qint64, etc.)

**The application provides:**
The Iterative factorial calculation algorithm
The Eratosthene's sieve algorithm
