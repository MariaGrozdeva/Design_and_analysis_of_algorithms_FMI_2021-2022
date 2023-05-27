function coinChange(denominations, value) {
  const ways = new Array(value + 1).fill(0);
  ways[0] = 1;

  for (const coin of denominations) {
    for (let i = coin; i <= value; i++) {
      ways[i] += ways[i - coin];
    }
  }

  return ways[value];
}
