# Project 02 - 🕸 PID Network Analysis

## 📚 Data
As the dataset, we will use [open data from Prague Integrated Transport (PID)](https://pid.cz/o-systemu/opendata/). Specifically, we will work with data from [timetables](https://pid.cz/o-systemu/opendata/#h-gtfs), which are originally in the GTFS (General Transit Feed Specification) format. This format is used by a wide range of software applications, and therefore public transport agencies, including PID, use it to publish their data.

☝️**Note!** For this homework, we will provide you with a prepared dataset $D$ in `csv` format. We compiled dataset $D$ for you from the data that comes from the [timetables](https://pid.cz/o-systemu/opendata/#h-gtfs). More information about all files and their attributes can be found in the [GTFS format documentation](https://developers.google.com/transit/gtfs/reference).

## Assignment
> ☝️ Use markdown cells! Justify all important steps, describe visualizations, and what can be observed from them. No points will be awarded for unclear homework.

Proper ongoing commenting and visual presentation of the process and results can earn up to 4 points. You are solving the assignment **individually**.

**✨ Dataset**
* Load the data from the file `d.csv`, which is the aforementioned dataset $D$, containing records for every two **consecutive** stops of a route.
* The structure is as follows (for simplicity, we do not consider service start_date and end_date):
| stop_from | stop_from_name | stop_to | stop_to_name | depart_from | arrive_to | route_type | is_night | mon | tue | wed | thu | fri | sat | sun |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| U699Z3P | Stadion Strahov | U981Z1P | Koleje Strahov | 7:24:00 | 7:25:00 | 3 | 0 | 1 | 1 | 1 | 1 | 1 | 0 | 0 |

* The unique identifier for a stop is the **stop name**. Be careful with the same stop names for different modes of transport - consider them as one and the same station.

**⚙️ Data Preprocessing**

* You may want to modify the attributes `depart_from` and `arrive_to`. They contain time values longer than 24 hours (this accounts for 1.5% of the records). From the GTFS format reference (info on the column from which `depart_from` and `arrive_to` were derived): _Arrival time at a specific stop for a specific trip on a route. … For times occurring after midnight on the service day, enter the time as a value greater than 24:00:00 in HH:MM:SS local time for the day on which the trip schedule begins._ However, you will also encounter incorrect times starting with values greater than 24. You can handle all these cases using **modulo 24** ☝️.

**🕸️ Basic Network Analysis** (total 12 points)

The task is to analyze the PID stop network. The stops will be the nodes of the network. There is a directed edge between two stops if they are consecutive stops of a route (there is at least one record in dataset $D$ with the corresponding `stop_from`, `stop_to`). The weight of the edge equals the number of transport vehicles that travel the route during one week.

Proceed as follows:
* Start by choosing any package for network analysis and visualization (you can also use the mentioned NetworkX),
* create a data representation from dataset $D$ suitable for the visualization package you chose,
* create a network visualization (total 4 points) - the visualization must be readable, so you can visualize a subset of the network (e.g., for a specific mode of transport, such as trams (except for visualizing the cable car or metro network, which we do not accept) or some subgraph - we leave the solution up to you),
* analyze the importance of stops over a week (Monday - Sunday) using at least three centrality measures and comment on what these measures mean in relation to the specific data (2 points for each measure, total 6 points),
* create a visualization for at least one centrality measure (total 2 points).

**❓ Your Own Questions** (3 points for each question, max. 9 points)

Create 3 questions (you can do more), based on filtering dataset $D$ and answer them with appropriate visualizations. Questions for inspiration:
* Do the important stops change depending on day/night operation?
* Is there a difference in stop load during the workweek/weekend?
* ...

**🔥 Additional Data**

In the file `stops.txt`, each stop is listed with its **latitude and longitude**. You can use this data to extend your analysis and it can also help you with graph layout. ☝️ Note the same stop names with slightly different locations for different modes of transport. You need to come up with a solution (e.g., first, average, centroid of the polygon, etc., according to your judgment) and justify it.

### Points Summary
Summary of points you can earn:
- 4 points for ongoing comments and visual presentation of the process and results,
- 4 points for network visualization,
- 6 points for a commented analysis of at least 3 centrality measures,
- 2 points for visualization of one of the centrality measures,
- 9 points for defining and answering at least three of your own questions.

In total, you can earn up to 25 points for Homework No. 2.
