# Game Theory - Fictitious Play

## Info
https://hackmd.io/Mp1x05shSXa0o2c1VUdlkg#6-References

## Example
![Example](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Example.png)

By the above two examples, the fictitious works normally and correctly in both pure-strategy and mixed-strategy case.

## Questions
### Q1. One pure-strategy Nash Equilibrium
![Q1](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q1.png)

In this case, the fictitious play converges to pure-strategy NE. As the image shows, r2 and c2 are the dominant strategy for P1 and P2 repectively. Therefore, the result of the fictitious play is correct. 

### Q2. Two or more pure-strategy NE
![Q2](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q2.png)

[r1, c1] and [r2, c2] are both NE, however, the fictitious play can only find one of them.
What interesting is that, given different belief in advance may change the final result of the fictitious play.

### Q3. Two or more pure-strategy NE (Conti.)
![Q3](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q3.png)



### Q4. Mixed-Strategy Nash Equilibrium
![Q4](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q4.png)

### Q5. Best-reply path
![Q5](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q5.png)

### Q6. Pure-Coordination Game
![Q6](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q6.png)

### Q7. Anti-Coordination game
![Q7](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q7.png)

### Q8. Battle of the Sexes
![Q8](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q8.png)

### Q9. Stag Hunt Game
![Q9](https://github.com/Angliu002/Fictitious-Play/blob/main/images/Q9.png)

## Download
```
git clone https://github.com/Angliu002/Fictitious-Play.git
```

## Compile
(You have to installed `make` in advance)
```
make
```

# Run
```
./test.sh
```

