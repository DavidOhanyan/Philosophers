# Philosophers

![philo](https://github.com/DavidOhanyan/Philosophers/assets/117384850/f4b54eff-faba-4203-808e-d267de2b83cf)


## Dining Philosophers Problem
The Dining Philosophers Problem is a well-known problem in computer science that serves as a classic example of common challenges in concurrent programming. This problem was originally conceived by Edsger Dijkstra in 1965 and can be summarized as follows:
<details>
<summary><i>Problem Description</i></summary>
X amount of philosophers sit at a round table with bowls of food.
Forks are placed in front of each philosopher.
There are as many forks as philosophers.
All day the philosophers take turns eating, sleeping, and thinking.
A philosopher must have two forks in order to eat, and each fork
may only be used by one philosopher at a time. At any time a
philosopher can pick up or set down a fork,
but cannot start eating until picking up both forks.
The philosophers alternatively eat, sleep, or think.
While they are eating, they are not thinking nor sleeping,
while thinking, they are not eating nor sleeping,
and, of course, while sleeping, they are not eating nor thinking.
</details>

## Data Races (Race Conditions) — What Are They?
Data races are a common problem in multithreaded programming. Data races occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior.

- two or more threads concurrently accessing a location of memory
- one of them is a write
- one of them is unsynchronized

In simpler words a race condition can happen when 2 or more threads are trying to access and modify the same variable at the same time, it can lead to an error in the final value of the variable.

## How to use it
Using `make` in the philo directory will create the `philo` executable.

You run it specifying, in order :

- The number of philosophers
- The time in milliseconds until a philosopher dies from starvation
- The time in milliseconds it takes for a philosopher to eat
- The time in milliseconds it takes for a philosopher to sleep
- (Optional) The number of meals before the program stops

`./philo 6 400 200 100 5`

Here, the program will create 6 philosophers, who will die if they go without eating for 400 milliseconds. It takes them 200 milliseconds to eat, and 100 milliseconds to sleep. The program will stop after each philosopher has had 5 meals (or if any one of them dies prematurely).
