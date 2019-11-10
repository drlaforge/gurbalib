/*
 Banking Code
  Loans: You can have max 2 loans out at the same time.
    - Good credit (Every 10 "pts" of good credit reduces the interest rate)
    - Bad credit (Every 2 "pts" of bad credit increases the interest rate)
    - Late payment - if you're late, you get 1 pt bad credit, and huge interest per day
*/

#define   WEEK          604800
#define   DAY          86400   /* Time in one day */

#define   MAX_LOAN     2000    /* Amount per level */
#define   GOOD_CREDIT  10      /* Good credit divisor */
#define   BAD_CREDIT   2       /* Bad credit divisor */
#define   HIGH_RISK    3       /* (*2) - no more loans */
#define   MAX_LOANS    2       /* Players can have this many at once */
#define   SEIZURE      2       /* Number of weeks until funds are seized */
#define   MIN_RATE     5       /* Good credit history */
#define   LOAN_RATE    9       /* Interest rate */
#define   LOAN_OVER_RATE 15    /* Interest rate */
#define   MAX_RATE     LOAN_OVER_RATE   /* Bad credit history */

#define   MAX_INVEST   2000    /* Amount per level */
#define   MAX_CDS      4       /* Players can have this many at once */
#define   INVEST_RATE  4       /* Interest rate */

#define   SAVINGS_RATE  0.02   /* 2% Dividend Rate */
#define   MIN_SAVINGS  100
#define MIN_LOAN     10000       /* Minimum loan amount */

