# Project 01 - 🕵️‍♀️ Exploratory Data Analysis

## 📚 Data
In the files `intakes.csv` and `outcomes.csv`, you will find data from a shelter in Austin, Texas, USA. The data comes from the official [Austin Open Data source](https://data.austintexas.gov/).

The [intakes](https://data.austintexas.gov/Health-and-Community-Services/Austin-Animal-Center-Intakes/wter-evkm) dataset contains data on animals received from October 1, 2013, to April 27, 2022. The [outcomes](https://data.austintexas.gov/Health-and-Community-Services/Austin-Animal-Center-Outcomes/9t4d-g238) dataset contains data on animals that left the shelter (e.g., were adopted, returned to the owner, etc.) during the same period. It is possible that animals received before October 1, 2013, are not present in `intakes.csv` (data was not collected yet) but will have a record in `outcomes.csv` if they left the shelter after this date.

☝️ Each dataset may **contain the same animal more than once** (1. some animals returned to the shelter - this complicates merging the datasets, but merging is not necessary for this assignment, 2. some records are duplicates - these can be removed as they are errors).

## Assignment
> ☝️ Use markdown cells! Justify all important steps, describe visualizations, and what can be observed from them. No points will be awarded for unclear homework.

Proper ongoing commenting and visual presentation of the process and results can earn up to 3 points.

**✨ Data Preparation** (total 4 points)
* Import the necessary packages.
* Load the intakes and outcomes datasets from the respective CSV files.
* Familiarize yourself with both datasets and comment on your findings:
  * Example information to discover: number of rows in the dataset, number and meaning of features, data type of features, and number of unique values, ...
* Clean and convert the data:
  * Determine how missing values are indicated in the dataset and if necessary, convert them to NaN.
  * Convert categorical features to the category type.
  * Convert the Age upon Intake/Outcome feature to a numeric feature.
  * Convert the DateTime feature to the datetime64 type.
  * Make any other modifications that make sense (convert other features, remove duplicate entries, add new features, ...).

**🖊️ Descriptive Statistics** (total 6 points)

Comment on the choice of appropriate statistics for the given data type and use visualizations whenever possible.
* Describe the Age upon Intake and DateTime features (originally from the intakes dataset) using univariate descriptive statistics.
* Select three other features and describe them using appropriate univariate descriptive statistics.
* Select two features that might have a relationship (e.g., correlation) and describe this relationship using bivariate descriptive statistics. The pair Age upon Intake and Age upon Outcome is not accepted.

**❓ Given Questions** (2 points for each question, max. 6 points)

Use appropriate visualizations to answer the following questions:
* Does the type of animal departure from the shelter (Outcome Type) depend on the type of intake (Intake Type)? If you prefer, consider only animals that appear exactly once in each dataset for simplification.
* Does the age of the animal play a role in adoption?
* Is the intake of animals constant throughout the year, or are there periods with higher/lower intake?

You can create multiple visualizations for one question if needed. Comment on the visualization results and all intermediate steps.

**❓ Your Own Questions** (2 points for each question, max. 6 points)

Come up with **at least three** of your own questions and answer them with appropriate visualizations. You can base your questions on the mentioned datasets. You can also use the third dataset [locations](https://data.austintexas.gov/Health-and-Community-Services/Austin-Animal-Center-Found-Pets-Map/hye6-gvq2) found in the file locations.csv, or you can download additional interesting data related to this topic.

The locations dataset provides information about all stray cats and dogs that have been in the shelter's database for **less than a week**. Most are in the shelter, but some are with volunteers – this information is indicated in the At AAC column (AAC – Austin Animal Center).

### Points Summary
Summary of points you can earn:
- 3 points for comments and visual presentation of the process and results,
- 4 points for data preparation,
- 6 points for descriptive statistics,
- 6 points for answering all given questions,
- 6 points for defining and answering at least three of your own questions.

In total, you can earn up to 25 points for Homework No. 1.