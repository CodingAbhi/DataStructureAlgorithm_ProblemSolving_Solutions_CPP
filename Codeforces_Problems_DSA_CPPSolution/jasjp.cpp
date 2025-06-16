public static int getMinimumOperations(List<Integer> items) {
    int n = items.size();
    int operations = 0;

    for (int i = 0; i < n - 1; i++) {
        while (items.get(i) % 2 == items.get(i + 1) % 2) {
            items.set(i + 1, items.get(i + 1) / 2);
            operations++;
        }
    }

    return operations;
}
