
### Code Structure:

```text
.
├── bin
│   ├── checksum.php
│   ├── composer.phar
│   └── evaluate.php
├── ci
│   └── docker_install.sh
├── composer.json
├── composer.lock
├── docker
│   ├── nginx
│   │   └── default.conf
│   ├── php7.4
│   │   ├── Dockerfile
│   │   ├── php.ini
│   │   └── xdebug.ini
│   ├── php8.1
│   │   ├── Dockerfile
│   │   ├── php.ini
│   │   └── xdebug.ini
│   └── postgres
│       └── Dockerfile
├── docker-compose.yaml
├── main.php
├── README.md
└── src
    ├── Events
    │   └── Event.php
    ├── ParkingMachines
    │   └── ParkingMachineCommand.php
    ├── Tests
    │   ├── Events
    │   │   ├── AbstractEventsTest.php
    │   │   ├── CreateDbTableTest.php
    │   │   ├── FindByIdTest.php
    │   │   ├── FindByVenueAndDateTest.php
    │   │   └── SaveTest.php
    │   ├── ParkingMachines
    │   │   ├── AbstractParkingMachineTest.php
    │   │   ├── ParkingMachineInputTest.php
    │   │   └── ParkingMachineOutputTest.php
    │   └── Triangle
    │       ├── TriangleBasicsTest.php
    │       ├── TriangleSimilarTest.php
    │       ├── TriangleSpecialTest.php
    │       └── TriangleTrait.php
    └── Triangle
        └── Triangle.php
```

# Final Task

The final task consists of three independent assignments. Each assignment has several parts for which you can earn
points. Tests are provided for each task, and your goal is to create an implementation according to the specifications
that meets the test conditions.

Each task has its own code in its respective namespace `FinalTask\TaskName`. The code can be found in the `src` folder
according to the task name.

The project also contains tests in the namespace `FinalTask\Tests`. You can use these tests to better understand the
requirements. **However, you must not modify them in any way.**

In the `bin` folder, there are scripts for evaluating tasks. You do not need to worry about these and you must not
change them either.

## Preparation

The project contains composer scripts with several commands to make certain steps easier. Before you start working,
install the dependencies using the following command:

```bash
$ composer install
```

## Running

If you want to run your interim solutions, create your own run.php or a similar script.

## Testing

To run the tests, you can use the following command:

```shell
$ composer test
```

If you want to run tests for a specific task or a specific TestCase, you can use phpunit directly:

```shell
$ vendor/bin/phpunit src/Tests/TaskName
$ vendor/bin/phpunit src/Tests/TaskName/SpecificTest.php
```

## Evaluation

Each task and its parts are assigned a certain number of points. The final evaluation will be based on the tasks passed
in the tests and may be adjusted by the instructor. You can find out the score of individual tasks and parts using the
following command:

```shell
$ composer evaluate
```

Another command is used to verify that no changes have been made to the tests or scripts for evaluating the results.

```shell
$ composer checksum
```

**If the checksum does not match, the entire final task will be automatically graded with 0 points.**

## Tasks

### 1) Triangle

The `Triangle` class represents a triangle with sides a, b, and c.

1. Implement the constructor and getters for sides a, b, and c.
1. If the input values violate the rule about the relative lengths of the sides and do not form a triangle, throw
   an `\Exception`.
2. If any input value is negative, throw an `\Exception`.
1. Implement the `isRight` method that returns whether the triangle is right-angled.
1. Implement the `isEquilateral` method that returns whether the triangle is equilateral.
1. Implement the `isIsosceles` method that returns whether the triangle is isosceles.
1. Implement the static method `Triangle::similar`, which has two parameters of type `Triangle` and returns whether the
   triangles are similar, i.e., their side lengths are in the same ratio.

### 2) (NOT IMPLEMENTED) Nearest Parking Meter Finder in Prague

Open data is available on the Prague geoportal [open data](https://www.geoportalpraha.cz/cs/data/otevrena-data/seznam).

One of these datasets is a GeoJSON
of [public parking meters](https://opendata.iprpraha.cz/CUR/DOP/DOP_ZPS_Parkomaty_b/WGS_84/DOP_ZPS_Parkomaty_b.json).

Your task is to create a Symfony Command that will read information from the console about the given latitude and
longitude and output the nearest parking meter (as the crow flies) along with some additional information.

The formatted output will include:

* **Distance** as the crow flies in kilometers,
* **City district** where the parking meter is located,
* **Total number of parking meters** in the city district where the nearest parking meter is located,
* **Link to open a map** with the location of the found parking meter.

Additional instructions:

* You can assume that the input is provided correctly. **You do not need to validate** the number and format of the
  parameters.
* You can download the JSON into PHP using, for example, the built-in `curl`, or you can install any dependency via
  composer.
* To calculate the distance between two geographic points, you need to use the _Haversine formula_. Find how it looks
  online. You **may** (unlike the rest of the solution) download the body of this function from the internet, and it
  will not be evaluated.
* When calculating the distance, consider the Earth's radius as **6371** km.
* Output the distance in kilometers formatted to exactly two decimal places. Use a period `.` as the decimal separator
  and a space ` ` as the thousands separator.

Example script execution and correct output:

```shell
php main.php parking-machine --latitude 14.49 --longitude 50.15
```

```text
The nearest parking meter is about 1.90 km away, located in the P8 district, where there are a total of 85 parking meters in the entire P8 district, https://maps.google.com/maps?q=50.136812557,14.478579329
```

### 3) Events

The `Event` class represents a concert, with an id, title, date, and venue, and can save itself to a database. For
database operations, use the `PDO` class, which is available in the `Event` class via the `$pdo` variable.

1. Implement the static method `createDbTable`, which creates a database table for storing events named `events`, if it
   does not already exist. The table must contain the following columns:
    1. `id INTEGER`
    2. `title TEXT`
    3. `date TEXT`
       4.`venue TEXT`
2. Implement the `save` method, which saves an instance of `Event` to the database by mapping the corresponding
   variables to the corresponding columns in the table.
    1. If an instance with the given `id` already exists, update the existing record.
    2. If an instance with the given `id` does not exist (also if the `id` is not set), save it as a new record and
       generate the `id`. You can generate it either in PHP or at the database level.
3. Implement the static method `findById`, which has one parameter `id` and finds the event in the database by id and
   returns its instance.
    1. If a record with the given `id` does not exist, return `null`.
4. Implement the static method `findByVenueAndDate` with the parameter `venue` and an optional parameter `date`, which
   finds all records with the given venue on the given date in the database and returns them as an array of `Event`
   instances.
    1. If the `date` is not provided, search only by venue.
    2. If no matching records are found, return an empty array.

