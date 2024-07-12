# Grinch's Sleigh

```text
What then!
The worst thing comes,
which always upsets the Grinch.
All the Whos down in Whoville, small and large,
gather together at the sound of Christmas bells,
hold hands... And singing fills the homes!

And it doesn't stop! That relentless singing!
Just SINGING! SINGING! SINGING! SINGING!
And the more the Grinch thought about their Christmas carols,
the more it gnawed at him: "I must stop this! Forever!
I've put up with this for a good thirty-five years!
And next year would be the same!"

And then he got an idea!
A horrible idea!
YES, THAT'S WHEN THE GRINCH
GOT A WONDERFUL, AWFUL IDEA!
```

The Grinch is the worst creature you have ever seen. From head to toe, he is covered in green fur, which he never brushes. He never bathes and smells awful. His teeth are filled with larvae, and he looks like a disgruntled crocodile. He is thoroughly evil and hates little children with all his heart. His heart is as hard as stone, and he detests Christmas and the entire Advent season. He decided to steal Christmas this year.

But stealing Christmas is not easy. It requires a proper plan! So the Grinch climbed to the highest peak of the mountain where his lair was located. While causing avalanches aimed at Whoville, he plotted his schemes. Yes, that's it! Christmas is mainly about presents. He needs to steal all the presents. But how?

The Grinch can't carry all the presents by hand, that's clear. And Whoville is too far for him to make multiple trips in one night. Just then, the Grinch heard distant barking. Yes, you're right, Max! We need a sleigh to load the stolen presents onto. And Max, the Grinch's only friend, will pull it!

The Grinch immediately set about executing his diabolical plan. If anyone dared to enter his cave, they would hear constant banging, hissing, welding, and cursing. Max wisely hid in the darkest corner of the cave and didn't show his nose at all.

Christmas is quickly approaching, and the Grinch is running out of time. The sleigh is still incomplete. Several important parts are still missing, such as a bell, antlers for Max, and the largest bag Whoville has ever seen. These items must be obtained immediately! So the Grinch summoned Max, gave him a map and a list of parts that needed to be collected right away. If Max tried to hide again, as he usually does, the Grinch promised to cut off his tail.

I haven't yet described enough to you, dear reader, what the Grinch's lair really looks like. This creature, over thirty-five years of his life, has woven a network of corridors and rooms throughout the mountain where he hoards his treasures. Or at least what he considers treasures. Here you can find various scattered bones of animals he ate or tortured, various trinkets he stole in town, found in a dump, or discovered during his wanderings in the hills.

Can you help save Max's skin and advise him on how to quickly collect all the necessary parts?

### Program Interface

Your task is to implement the function `std::list<Place> find_path(const Map &map)` that finds the shortest possible walk in the given map, collecting at least one part of each type. The first element of the walk must be `map.start`, the last `map.end`, and there must be a corridor between each pair of consecutive places. If such a walk does not exist, return an empty list. The `Map` structure contains the following items:

- `places`: the number of rooms in the Grinch's lair,
- `start`, `end`: the room numbers where Max starts and where he needs to bring the collected items (numbered from zero),
- `connections`: a list of pairs of rooms describing the corridors,
- `items`: a list of lists, `items[i]` is a list of rooms where the i-th part is located.

You can assume that the room numbers are always in the range from 0 to `places - 1` (inclusive).

### Scoring Conditions

- For 2 points, you need to determine if such a walk exists. If so, return any non-empty list; its content is not checked. The instance size is the same as for 5 points.
- For 5 points, you need to correctly and quickly solve instances with approximately 1000 rooms and up to 4 types of items. Each item can be found in many rooms.
- For 10 points, you need to correctly and quickly solve instances with approximately 3000 rooms and up to 6 types of items. Each item can be found in many rooms.
- Bonus: For 13 points, you need to correctly and quickly solve instances with approximately 10,000 rooms and up to 12 types of items. However, each item is found in no more than 5 rooms.
