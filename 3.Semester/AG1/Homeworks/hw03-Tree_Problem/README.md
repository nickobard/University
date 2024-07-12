And that's something I forgot to tell you last time. The Whos love Christmas so much that they have a decorated tree at home all year round. In the toy store, they have not only Summer Christmas but also Autumn and Spring Christmas. Our green alien doesn't come close to that. And last but not least, it should be mentioned that the street system in Whoville is also tree-shaped. Not very practical, but nobody here minds.

What is little known, even among the Whos, is that this small village has its own secret services. The unit is called the Grinch Resistance Unit (GRU), and its main task is, of course, to protect Whoville and Christmas from the malice of this universally hated creature.

Immediately after the secret service agents picked up the first hints of what the Grinch was planning, Whoville's security council convened. They began preparing countermeasures. We do not know all the steps they prepared. But there is one thing I can tell you about, as it directly concerns you.

Due to being the owner of the only toy store in Whoville and the recently established Advent Market Registry (AET), the Mayor has complete oversight of who bought what, where, and when. Thus, he also knows what can be expected under each Christmas tree on Christmas night.

Since you proved yourself in preparing the Bestselling Products, the Mayor decided to approach you for this job as well. Your task is to find the placement of secret service agents in the streets of the town to protect as many gifts as possible. According to ancient customs, gifts always appear under trees located at intersections and squares so that the Whos can immediately share the joy of the gifts with others.

But beware! Under no circumstances should the Whos notice the agents in the streets. If panic were to break out among the residents on Christmas Eve, the Mayor might not be able to handle it. Therefore, make sure that large groups of agents do not appear close to each other in the streets. Agents are considered part of the same group if there is no unguarded tree between them.

### Program Interface

Your task is to implement the function `uint64_t solve(const TreeProblem&)` which calculates how many gifts can be protected with the best possible placement of guards. The problem instance is described by the `TreeProblem` structure, which contains the following items:

- `max_group_size`: The maximum size of a group of guards. This value is 2 in the bonus test case and 1 otherwise.

- `gifts`: A vector specifying how many gifts are under each tree. The length of this vector also indicates the total number of trees.

- `connections`: A vector of pairs indicating which trees are at opposite ends of the same street, so if both are guarded, their guards belong to the same group. We remind you that the network of Whoville's streets forms a tree.

### Scoring Conditions

- For 3 points, the implementation needs to work on small inputs with `max_group_size = 1`.

- For 6 points, a naive exponential implementation is not sufficient.

- For 10 points, the implementation must be efficient, the inputs are large, and the stack size is limited to 1 MiB.

**Bonus:** For 13 points, it is necessary to correctly solve instances with `max_group_size = 2` of a size similar to the previous point.
