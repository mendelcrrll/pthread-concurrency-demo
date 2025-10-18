# CSE333 TA Demo: Concurrent Donations

## <span style="color: Chartreuse;">Slide 1: Introduction</span>  

**Topic:** Thread concurrency and race conditions in C++ using pthreads  
**Goal:** Demonstrate how multiple threads updating a shared variable can cause inconsistencies — and how mutexes prevent them  

---

### Step Up / Story Context

- Race conditions occur when two or more threads access and modify shared data at the same time.  
- We’ll simulate a nonprofit donation system with multiple donor threads.  
- Imagine *CompSi 4 All*, a nonprofit that offers free CS programs for low-income communities.  
- The organization is hosting a major fundraiser, where multiple donors submit donations through a shared online portal.  
- Each donor thread represents one person contributing to the shared total.

Next, we’ll look at what happens *without any protection* — and watch the race condition unfold.

---

## <span style="color: Chartreuse;">Slide 2: Raw Demo Overview</span>  

### Setup
This class has famously strict coding style. We are going to take a look at this **raw version** of a concurrent program and try to make sense of it. Commenting is a key step in the process so we will do that first and see what we learn along the way.

### Live Commenting Exercise 

Our goal:  
1. **Go line by line**, adding comments to explain what’s happening.  
2. Identify **where the race conditions can occur**.  
3. Briefly predict how the program might misbehave.

Ask yourself:

- “What does this line do?”  
- “What variables are shared between threads?”  
- “What happens if two threads hit this at the same time?”

Commenting example:

```c++
// Shared variable: unsafe access across threads
// Race condition likely occurs here: total_donations += donation
// No locking mechanism used — multiple threads may update simultaneously
```



## <span style="color: Chartreuse;">Slide 3: Live Demo</span>  

**Live Demo Transition:**  
Let’s run it and watch how concurrent updates lead to unpredictable behavior:

>  g++ -pthread pthread_donations_demo_raw.cc -o demo
>
>  ./demo_raw

---

### Discussion

- Why might this happen even though each donor runs the same code?  
- Which specific line of code could be problematic?  
- What does it mean that multiple threads “share” a variable?

---

<details>
<summary> Click to reveal insight</summary>

### What we may have found is:

- `total_donations += donation` is **not atomic**.  
- Threads may read the same value before either writes back.  
- One update overwrites another → a **lost update**.  
- This is the core of a **race condition**.

</details>

---

## <span style="color: Chartreuse;">Slide #4: Solutions – Fixing the Race Condition</span>  

### Student Solutions
*(Write ideas or notes from the class discussion here.)*

-  

---

### Code Fix Hypotheses
*(Students propose or discuss possible fixes.)*

-  

---

<!-- Space left intentionally blank for live class brainstorming -->














<details>
<summary>Click to reveal solution</summary>

### Correct Fix: Using a Mutex
- Introduce a `pthread_mutex_t` to control access to the shared variable `total_donations`.  
- Initialize it once in `main()` with `pthread_mutex_init(&balance_lock, nullptr);`.  
- Surround the critical section with:
  ```cpp
  pthread_mutex_lock(&balance_lock);
  total_donations += donation;
  pthread_mutex_unlock(&balance_lock);
  ```

</details>

## <span style="color: Chartreuse;">Slide #5: Let's Run and Debug!</span>  

### Run the Fixed Version

Now we’ll test our **mutex-protected** program and confirm that our solution works.

Observe:
- Are all intermediate totals consistent?  
- Does the final total always match the sum of all donations?  
- Is there any unexpected behavior remaining?

---

### Debugging Discussion

Record what you see and discuss:
- Did the output still vary between runs?  
- If so, does that necessarily mean it’s incorrect?  
- Which parts of the program still run concurrently, even with a mutex?

---

### Class Debugging Notes
*(Use this space to write class observations during the live demo.)*

-  

-  

---

<!-- Space left intentionally blank for live class brainstorming -->















<details>
<summary>Click to reveal debugging insights</summary>

### Instructor Notes

- Even though the totals vary in **order**, the final total is now always correct.  
- The randomness remains due to thread scheduling and `rand()` calls, not a race condition.  
- Every donation is now reflected exactly once because `pthread_mutex_lock()` guarantees exclusive access.  
- This demonstrates the key concept: **concurrent execution ≠ data races** — concurrency is fine as long as shared access is controlled.

---

**Transition:**  
We’ve now seen the full cycle:
1. Raw version → race condition  
2. Diagnosis → commenting and reasoning  
3. Mutex fix → consistent behavior  

</details>

---

## <span style="color: Chartreuse;">Slide #6: Summary</span>

### Key Takeaways

- **Race conditions** occur when multiple threads access and modify shared data at the same time without synchronization.  
- Even small code sections, like `total_donations += donation`, can cause unpredictable results when executed concurrently.  
- **Mutexes** (`pthread_mutex_t`) provide *mutual exclusion* — ensuring only one thread enters a critical section at a time.  
- Proper synchronization preserves **correctness**, while still allowing **concurrency**.

---

### Reflection

- What other issues like this might a nonprofit run into?
- What are other examples where synchronization is necessary in systems programming?  
- Can using too many locks cause problems?

---

### Student Takeaways
*(Add class conclusions or open questions here.)*

-  

-  

---

<!-- Space left intentionally blank for live class brainstorming -->













<details>
<summary>Click to reveal instructor wrap-up</summary>

### Instructor Notes
- This exercise demonstrated both **data races** and **mutual exclusion** at a very visible level.  
- Students should now understand that **concurrency itself isn’t bad** — *uncontrolled* concurrency is.  
- Reinforce that thread safety and performance often require **balancing** synchronization and parallelism.  

</details>

---
