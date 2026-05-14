# Maximum Subarray Sum — Kadane’s Problem

A small C project for our algorithms course. We had to solve the same problem in two ways: one with a normal loop, and one with recursion. Nothing fancy — just clear code and a README we can actually use before the presentation.

---

## Team members

| # | Name |
|---|------|
| 1 | Naira Mohamed Fawzy |
| 2 | Lenda Ayman Abdou |
| 3 | Mariam Mohamed Mohamed Mounir |
| 4 | Mariam Ibrahim Mohamed |
| 5 | Farah Hany Elsayed |
| 6 | Christine Emil Abd El Masih |
| 7 | Mariam Ali Abd Elhalim |

*(If anything is spelled wrong for official documents, tell us and we fix it in one minute.)*

---

## What is this project about?

We get an array of integers (positive, negative, or mixed). We need the **largest sum** we can get from a **contiguous** block — meaning elements that sit next to each other in order, no skipping.

Example: `[-2, 1, -3, 4, -1, 2, 1, -5, 4]` → the answer is **6** (from the block `4, -1, 2, 1`).

We implemented **Kadane’s idea** twice:

1. **`kadane_non_recursive/`** — classic loop version (`kadane_max_sum`).
2. **`kadane_recursive/`** — same logic but `maxEnd` calls itself (`maxSubArr` + global `maxSum`).

Both programs read `n`, then `n` numbers, and print the maximum subarray sum.

---

## Project structure

```
proj_algo/
├── README.md                 ← this file
├── PROJECT_REPORT.md         ← longer write-up for submission / Word
├── kadane_non_recursive/
│   └── main.c
└── kadane_recursive/
    └── main.c
```

---

## How to compile and run

Open a terminal **inside** the `proj_algo` folder.

**Loop version:**

```bash
gcc kadane_non_recursive/main.c -o kadane_loop
./kadane_loop
```

**Recursive version:**

```bash
gcc kadane_recursive/main.c -o kadane_rec
./kadane_rec
```

On Windows (MinGW / similar):

```text
gcc kadane_non_recursive/main.c -o kadane_loop.exe
kadane_loop.exe
```

Same idea for the recursive folder.

**Sample interaction**

- Program asks: `Enter number of elements:`
- You type: `9` then Enter  
- Then you type the 9 numbers (space or newline between them is fine for `scanf`).

---

## Pseudocode — Recursive version (`kadane_recursive`)

*(This matches how we think about the program step by step.)*

1. **Start**

2. Read number of elements **n**

3. Input array elements into **nums[]**

4. **Set:**  
   `maxSum = nums[0]`

5. **Define recursive step** (conceptually what `maxEnd` does for index `i`):

   - If `i == 0`  
     → return `nums[0]`

   - **current** = maximum between:  
     - `nums[i]`  
     - `nums[i] + Recursive(i - 1)`

   - If **current** > **maxSum**  
     → `maxSum = current`  
     *(In our C code we used `max(maxSum, curr)` — same meaning.)*

   - Return **current**

6. Call **Recursive(n − 1)**  
   *(In code: `maxEnd(nums, n - 1)` after `maxSum` was initialized.)*

7. Print **maxSum**

8. **End**

---

## Pseudocode — Non-recursive version (`kadane_non_recursive`)

1. **Start**

2. Read number of elements **n**

3. Input array elements into **nums[]**

4. **Set:**  
   `curr_sum = nums[0]`  
   `max_sum = nums[0]`

5. **Repeat** from `i = 1` to `n − 1`:

   - If `nums[i] > curr_sum + nums[i]`  
     → `curr_sum = nums[i]`

   - **Else**  
     → `curr_sum = curr_sum + nums[i]`

   - If `curr_sum > max_sum`  
     → `max_sum = curr_sum`

6. Print **max_sum**

7. **End**

---

## Analysis — what actually happens?

### Analysis steps — Non-recursive (loop) *(simple)*

1. Read the whole array (or get it from `main`).
2. Start with the first element: that is both the “best sum ending here” and the “best sum so far.”
3. Move to the next element. Decide: **add** it to the previous chain, or **restart** the chain at this element only — keep the better sum as `curr_sum`.
4. If this new `curr_sum` is bigger than everything we saw before, save it in `max_sum`.
5. Repeat step 3–4 for every position until the end of the array.
6. `max_sum` is the answer.

### Non-recursive (loop) — short explanation

- We walk the array **once**, from left to right.
- **`curr_sum`** always means: “best sum of a subarray that **ends right here** at index `i`.”  
  Either we **restart** at `nums[i]` or we **extend** the previous chain — we pick the better one.
- **`max_sum`** remembers the **best value we ever saw** along the way, so even if `curr_sum` drops later, we don’t lose the old peak.
- After the loop, **`max_sum`** is the answer for the whole array.

### Analysis steps — Recursive (`maxEnd`) *(simple)*

1. Set `maxSum` to the first element (starting guess for the global best).
2. Call `maxEnd(nums, n − 1)` — “tell me the best sum ending at the last index.”
3. Inside `maxEnd` for index `i`: if `i == 0`, return `nums[0]` (**base case** — only one element).
4. If `i > 0`, first get the answer for `i − 1` by calling **`maxEnd` again** (smaller index).
5. Combine: best ending at `i` = **max**(`nums[i]`, `nums[i]` + answer from step 4).
6. Update `maxSum` if this combined value is better.
7. Return the “best ending at `i`” upward; when all calls finish, `maxSum` holds the maximum subarray sum.

### Recursive (`maxEnd`) — short explanation

- We still care about “best sum **ending at** index `i`,” but instead of a `for` loop we **ask the smaller problem first**: best ending at `i−1`, then combine with `nums[i]`.
- Base case: index `0` → only one element, return `nums[0]`.
- Each return from a deeper call gives the “best ending at that index”; we update **`maxSum`** whenever the current ending-sum beats the global best.
- So it’s the **same math as Kadane**, just written as **self-calling functions** instead of one loop.

---

## Complexity — short and honest

### Non-recursive (iteration method)

| | |
|---|---|
| **Time** | **O(n)** |
| **Extra space** | **O(1)** |

#### Complexity proof steps — iteration (loop) method

**A) Time complexity = O(n) — step by step**

1. **Before the loop:** we set `curr_sum` and `max_sum` to the first element. That is a fixed number of assignments — it does **not** grow when `n` grows → **O(1)**.

2. **The loop:** we have `for (i = 1; i < n; i++)`, so `i` runs from `1` to `n - 1`. The loop body runs **`(n - 1)` times**, i.e. **Θ(n)** iterations.

3. **Inside each iteration:** a few comparisons and assignments to update `curr_sum` and `max_sum`. No inner loop over the whole array. The work per iteration is **bounded by a constant** → **O(1)** per iteration.

4. **Putting it together:**  
   total time for the loop ≈ `(number of iterations) × (work per iteration)`  
   = `(n - 1) × O(1)` = **O(n)**.

5. **Return statement:** one return → **O(1)**.

6. **Conclusion for `kadane_max_sum`:**  
   `O(1) + O(n) + O(1)` = **O(n)** time.

*(Oral-exam note: `main` also has a loop to read `n` values — that is **O(n)** too. If you count the **whole program** from input to print, total time is still **linear in n**.)*

**B) Space complexity = O(1) extra — step by step** *(for the function itself, not counting the input array as “extra”)*

1. **Local variables in `kadane_max_sum`:** `i`, `curr_sum`, `max_sum`. That is a **fixed count**; we do not add more variables when `n` increases.

2. **No auxiliary array** of size depending on `n` is allocated inside the function (no `copy[n]`-style structure).

3. **No recursion** → no call stack that grows with `n` for this function.

4. **Conclusion:** extra memory used by the function is **constant** → **O(1)** extra space.

*(The array `nums` in `main` has size `n` — that is the **input** to the problem. In algorithm analysis we usually report **auxiliary space** besides the input, which is why the loop Kadane answer is **O(1)**.)*

### Recursive

| | |
|---|---|
| **Time** | **O(n)** — we still effectively solve “ending at `i`” for each `i` once along the chain of calls. |
| **Extra space (stack)** | **O(n)** in the worst case — deepest call chain is from `n−1` down to `0`, so about **`n` stack frames** at the worst moment. |

Why O(n) time? One “wave” of recursion: you go down to `i = 0`, then come back up updating each index once.

Why O(n) stack? Each recursive call waits for the next; the stack depth follows the length of that chain, not constant like the loop.

#### Complexity proof steps — recursive Kadane (recurrence)

Think of `T(n)` as the total time for the recursive chain that starts at index `n − 1` and keeps calling `maxEnd` with a smaller index until it hits `i = 0`. Each call does **constant** work besides the recursive call, so we can write:

```
T(n)   = T(n − 1) + 1
T(n−1) = T(n − 2) + 1
```

**Substitute:**

```
T(n) = T(n − 2) + 2
```

**Continue expanding:**

```
T(n) = T(n − 3) + 3
```

**After k steps:**

```
T(n) = T(n − k) + k
```

**When** `n − k = 0`, then **`k = n`**. So:

```
T(n) = T(0) + n
```

`T(0)` is **constant** (the base case `i == 0`). Ignoring constants:

**`T(n) = O(n)`**

*(Same idea if you write the recurrence in terms of the index `i`: each `maxEnd(nums, i)` does O(1) work plus `maxEnd(nums, i − 1)` until `i = 0`.)*

### One line to remember for the oral

Same problem, same **O(n)** time, but the **loop version is nicer for memory** (**O(1)** extra) while the **recursive version pays with the call stack** (**O(n)**).

---

## Notes we kept in mind

- Programs assume **n ≥ 1** (we didn’t add heavy validation — course demo style).
- **VLA** `int nums[n]` needs a compiler that supports C99 variable-length arrays (gcc usually OK; MSVC in older modes can complain — if that happens, switch to `malloc` or a fixed max size).

---

## Word documentation (simple)

- **`Project_Documentation.docx`** — same text as this README, but saved as a **plain Word file** (almost no formatting on purpose).
- **`Project_Documentation.word`** — **copy of the same file** with a `.word` extension (some PCs need “Open with → Word”, or rename to `.docx`).
- To **regenerate** both files after you edit the script:  
  `powershell -ExecutionPolicy Bypass -File build_word_doc.ps1`

---

## Files worth opening before the demo

1. `kadane_non_recursive/main.c` — `kadane_max_sum` + `main`
2. `kadane_recursive/main.c` — `maxEnd`, `maxSubArr`, `maxSum`
3. `PROJECT_REPORT.md` — dry run table + longer explanation if the doctor asks for a report

Good luck to the team.
