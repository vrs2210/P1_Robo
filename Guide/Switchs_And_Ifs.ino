int Variable = 1; // We just have a normal variable here, could be anything of any type.

void setup() {
  // We don't initialize anything, as there's no need to.
}

// Inside of this loop, both of these code segments are identical in functionality.
/*
The benefits of using switch cases over if statements is that it is more performant if you have a lot of if statements.
Switch cases immediately find what case it is, whereas if statements have to search through each statement.
The problems with switch cases is that they can't have complex conditionals, i.e X > 10 && x < 50.
Additionally, they are unable to use floating point values, which are numbers with decimal places.

I won't list the pros and cons, but here are the recommended guide for which to use at certian situations;

Use if/else when:
- You have complex conditions (x > 10 && x < 50).
- You have sparse or widely spread cases (x == 1 || x == 100 || x == 500).
- You are working with floating point numbers.

Use Switch/case when:
- Cases are dense and sequential (1, 2,3, 4, ...)
- You want faster execution.
- You are handling many cases.
*/

void loop() {
  switch (Variable) {
    case 1: // We check if Variable is equal to 1.
      break;
    case 2: // We check if Variable is equal to 2.
      break;
    case 3: // We check if Variable is equal to 3.
      break;
    default:  // We check if Variable is neither of the three cases.
      break;
  }

  if (Variable == 1) {  // We check if Variable is equal to 1.

  } else if (Variable == 2) {  // We check if Variable is equal to 2.
    
  } else if (Variable == 3) { // We check if Variable is equal to 3.

  } else { // We check if Variable is neither of the three if statements.

  }
}
