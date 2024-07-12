"""
In this homework, we will use well-known Titanic dataset which contains 
information about passengers of Titanic. The dataset consists of personal 
information about each passenger and indicator whether the passenger 
survived. We will use this data to analyse passenger list and their chance for
survival.

The provided dataset contains the following attributes:
 'Age' - age in years,
 'Fare' - fare ticked price,
 'Name' - passenger name,
 'Parch' - # of parents/children of a person on board,
 'PassengerId' - identifier,
 'Pclass' - travelling class, 1 = 1. class, 2 = 2. class, 3 = 3. class,
 'Sex' - sex,
 'SibSp' - # siblings/spouses on board,
 'Survived' - 0 = died, 1 = survived,
 'Embarked' - boarding port C = Cherbourg, Q = Queenstown, S = Southampton,
'Cabin' - cabin number
 'Ticket' - ticket number
"""
import numpy as np
import pandas as pd
import numpy


def load_dataset(train_file_path: str, test_file_path: str) -> pd.DataFrame:
    """
    Write a function which loads CSV from two files to pandas DataFrame and
    performs several data processing steps. Use data provided in `data`
    directory for testing ('data/train.csv' as input parameter
    `train_file_path`, and 'data/test.csv'  as `test_file_path`). Add column
    name "Label" to each DataFrame. The column should contain value "Train"
    for data from `train_file_path` and "Test" from test_file_path.
    
    Perform following operations with DataFrames (keep the order of the
    operations):
        1. Concatenate both DataFrames.
        2. Remove columns  "Ticket", "Embarked", "Cabin" from created DataFrame.
        3. Set the index to unique numbers from zero to the number of rows.

    The return value of the function is processed DataFrame.
    """

    train_data = pd.read_csv(train_file_path)
    test_data = pd.read_csv(test_file_path)

    train_data['Label'] = 'Train'
    test_data['Label'] = 'Test'

    concatenated_data = pd.concat([train_data, test_data]) \
        .reset_index(drop=True) \
        .drop(['Ticket', 'Embarked', 'Cabin'], axis=1)

    return concatenated_data


def get_missing_values(df: pd.DataFrame) -> pd.DataFrame:
    """
    When working and analysing data, one often needs to deal with missing
    values. For example, some passengers did not fill information about
    family members. In that case, one needs to be aware of it as it may
    introduce bias to the data.

    Write a function which determines the number of missing values in given
    DataFrame. The function should output a new DataFrame. The new DataFrame
    should be indexed by columns of original DataFrame. Columns of returned
    DataFrame will be (keep the order of the columns):
        1. "Total" - contains the number of missing values
        2. "Percent" - contains the percentage of missing values with regard to all
        rows of given DataFrame.

    Sort the resulting DataFrame based on the number of missing values from
    largest to smallest.
    
    Example of output:

               |  Total  |  Percent
    "Column1"  |   34.5  |    76.54321
    "Column2"  |   0     |    0
    """
    result_frame = pd.DataFrame()
    for column in df.columns:
        number_of_nans = df[column].isnull().sum()
        percentage = (number_of_nans / len(df)) * 100
        row_frame = pd.DataFrame({'Total': number_of_nans, 'Percent': percentage}, index=[column])
        result_frame = pd.concat([row_frame, result_frame])
    return result_frame.sort_values(by=['Total'], ascending=False)


def substitute_missing_values(df: pd.DataFrame) -> pd.DataFrame:
    """
    One way how to handle missing data is to substitute missing values with
    some statistic of other rows. We will use this method for two columns:
        1. "Age" - fill missing values with the mean of other rows.
        2. "Fare" - fill missing values with the lowest price of ~$15 (we
        suppose that the majority of unregistered tickets were the cheapest
        ones).

    Do not to modify given DataFrame but create a copy of it.
    """

    data = df.copy()

    age_mean = data['Age'].mean()
    default_fare = 15

    data.loc[data['Age'].isnull(), 'Age'] = age_mean
    data.loc[data['Fare'].isnull(), 'Fare'] = default_fare

    return data


def get_correlation(df: pd.DataFrame) -> float:
    """
    We want to know whether there is a relationship between the age of a
    passenger and fare ticket price (e.g. younger children have cheaper
    tickets). We will use Pearson correlation coefficient to quantify linear
    relationship between columns "Age" and "Fare".
    The result will be returned as one number.

    Pearson correlation coefficient quantifies linear relationship between
    two random variables. Correlation ranges from -1 to 1. Value around zero
    indicates no linear relationship, -1 indicates strong negative
    relationship, 1 indicates strong relationship.
    """
    return df[['Age', 'Fare']].corr(method='pearson').loc['Age', 'Fare']


def get_survived_per_class(df: pd.DataFrame,
                           group_by_column_name: str) -> pd.Series:
    """
    We want to know how big was the chance of survival for different groups of
    passengers (e.g. for different sexes, classes, etc.). Write a function
    that estimates that. The input of the function is a DataFrame with data
    and name of column (group_by_column_name) which holds group information.
    To increase readability of the result sort values from the highest chance of
    survival to lowest and round the resulting values to 2 decimal places.
    Return result as pandas Series.
    
    Example:

    get_survived_per_class(df, "Sex")

                  Survived
    Female     |      0.82
    Male       |      0.32

    """
    survived = df[df['Survived'] == 1]
    all_passengers = df[df['Survived'].notnull()]

    all_passengers_by_group = all_passengers.groupby(group_by_column_name)['Survived'].count()
    all_survived_by_group = survived.groupby(group_by_column_name)['Survived'].count()

    survival_ratio = all_survived_by_group / all_passengers_by_group
    survival_ratio.round()
    return survival_ratio.sort_values(ascending=False).round(decimals=2)


def get_outliers(df: pd.DataFrame) -> (int, pd.DataFrame):
    """
    We want to explore fare ticket prices. An important part of such
    exploration is exploration of outliers. An outlier may indicate an error
    in the data (somebody entered price incorrectly) or some special group of
    passengers.

    We will use the IQR method for the identification of outliers. IQR method
    considers an outlier any point which does not fulfil:
        Q1 - 1.5*IQR < point_value < Q3 + 1.5*IQR,
    where Q1 and Q3 are the first and the third quartiles respectively
    calculated from all points in data. IQR is the inter-quartile range
    calculate as the difference between Q3 and Q1:
        IQR = Q3 - Q1.

    Return tuple with the number of outliers and all passengers with outlier
    fare ticket price.
    """

    fares = df['Fare'].sort_values().reset_index(drop=True)

    q1 = fares.loc[len(df) // 4]
    q3 = fares.loc[(len(df) * 3) // 4]

    iqr = q3 - q1

    lower_bound = q1 - 1.5 * iqr
    upper_bound = q3 + 1.5 * iqr

    outliers = df[(df['Fare'] <= lower_bound) | (df['Fare'] >= upper_bound)]

    return len(outliers), outliers


def create_new_features(df: pd.DataFrame) -> pd.DataFrame:
    """
    To analyse data and use them for modeling, it may be convenient to create
    a new columns (features). These new features are usually created
    transformation of original values. For example, if we want to compare
    survivals from Titanic and SS Eastland we will want to scale fare prices
    to the same values for each ship as travelling on Titanic was more
    expensive.

    Create 3 new variables:
        1. "Fare_scaled" - scale "Fare" columns to have zero mean and standard
       deviation equal one.
        2. "Age_log" - is natural logarithm of attribute "Age" (differences
        between age of children are magnified in comparison to adults).
        3. "Sex" -  Replace string values with numerical ones, where "male"
        will be replaced with 0 and "female" with 1. The resulting values
        should have type `int`.

    Do not modify original DataFrame.
    """
    data = df.copy()
    zero_mean_fares = data['Fare'] - data['Fare'].mean()
    scaled_fares = (zero_mean_fares / data['Fare'].std()).rename('Fare_scaled')

    data = pd.merge(data, scaled_fares, left_index=True, right_index=True)

    data['Age_log'] = numpy.log(data['Age'])

    data['Sex'] = data['Sex'].replace('male', int(0))
    data['Sex'] = data['Sex'].replace('female', int(1))

    return data


def determine_survival(df: pd.DataFrame, n_interval: int, age: float,
                       sex: str) -> float:
    """
    Determine the probability of survival of a person specified by age and sex.

    Missing values in column "Age" replace with mean value. In order to
    moderate significance of the estimated probability, divide "Age" to
    specified number of intervals and calculate probability from given
    interval. For example if we have values in "Age" column [2, 13, 18, 25] and
    we want 2 intervals, result should be:

    0    (1.977, 13.5]
    1     (13.5, 25.0]

    With division based on "Sex", the categorization should be:

       "AgeInterval" | "Sex"       |   "Survival Probability"
       (1.977, 13.5] | "male"      |            0.21
       (1.977, 13.5] | "female"    |            0.28
       (13.5, 25.0]  | "male"      |            0.10
       (13.5, 25.0]  | "female"    |            0.15

    Output of determine_survival(df, n_interval=2, age = 5, sex = "male")
    should be 0.21. If there is no passenger for some group, return numpy
    NA value.
    """

    if sex != 'male' and sex != 'female':
        return np.NAN

    relevant_df = df[['Sex', 'Survived', 'Age']].copy()
    relevant_df.loc[relevant_df['Age'].isnull(), 'Age'] = relevant_df['Age'].mean()

    min_age = relevant_df['Age'].min()
    max_age = relevant_df['Age'].max()

    if age > max_age or age < min_age:
        return np.NAN

    interval_step = (max_age - min_age) / n_interval
    intervals = list()
    for i in range(0, n_interval):
        lower_bound = interval_step * i + min_age
        upper_bound = interval_step * (i + 1) + min_age
        interval = pd.Interval(left=lower_bound, right=upper_bound)
        intervals.append(interval)

    relevant_df = relevant_df.assign(AgeInterval=np.NAN)

    for iv in intervals:
        relevant_df.loc[relevant_df['Age'].between(iv.left, iv.right), 'AgeInterval'] = iv

    survived = relevant_df[relevant_df['Survived'] == 1]

    all_passengers_grouped = relevant_df.drop('Age', axis=1).groupby(['AgeInterval', 'Sex']).count()
    survived_grouped = survived.drop('Age', axis=1).groupby(['AgeInterval', 'Sex']).count()

    result = survived_grouped / all_passengers_grouped
    try:
        prob = result.loc[(age, sex), 'Survived']
    except KeyError:
        return np.NAN
    return prob
