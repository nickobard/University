The third homework for the BI-VIZ subject.

The work is being done in the team of three.

My part of work:

- Further analysis of linearity and non-linearity in the dataset
- AdaBoost model and its visualizations

# Project 03 - 📈 Visualization in Machine Learning from A to Z

## 📚 Data

For this assignment, students **choose suitable data themselves**. ☝️ The chosen data should be publicly available and
should simulate or correspond to a real-world situation (i.e., synthetic/generated data is not considered!). Choose data
that allows you to solve a classification or regression task (i.e., supervised learning, presence of an output
variable).

**For the brave:** If you feel confident, you can also choose an unsupervised task, e.g., clustering.

#### Tips on data and solutions

In the file `datasets_tips.md`, you can find tips on various public websites with datasets.

Inspiration for completing the assignment can be found in practical examples for lectures No. 8 (exercise 4) and 11.
However, copied code will not be positively evaluated.

☝️**Note!** Try to choose a somewhat imaginative dataset. If you choose a dataset that is often part of tutorials (
e.g., [Titanic dataset](https://www.tensorflow.org/datasets/catalog/titanic)
or [Iris dataset](https://scikit-learn.org/stable/modules/generated/sklearn.datasets.load_iris.html#sklearn.datasets.load_iris)),
you will likely need to put in extra effort for creative and original presentation to earn full points.

## Assignment

> ☝️ Use **markdown cells**! Justify all important steps, describe visualizations, and what can be observed from them.
> Points will not be awarded for a disorganized homework assignment.

You can earn up to 5 points for thorough commentary and visual presentation of the process and results. Submit the
notebook after running it (including output cells) and ensure that comments are correctly displayed ('rendered file' on
GitLab in your browser).

You can complete the assignment as **individuals** or in a **group of up to 3 classmates**. The procedure for group
evaluation can be found on the course
pages [here](https://courses.fit.cvut.cz/BI-VIZ/homeworks/index.html#_podrobnosti-k-hodnocen%C3%AD-třet%C3%ADho-úkolu).

### Instructions for completion

🙏 If possible, use **visualizations** at each step of your work and comment on your findings.

**📖 Your task:**

1. Describe the classification/regression task you will be solving in this homework assignment.
2. State the source of your data. ⛔️ Note: If you are working with a locally stored dataset, submit it along with the
   completed Jupyter Notebook via GitLab so that the instructor can work with the data during grading.

**✨ Dataset:**
In this section, you are to load the chosen data and get to know it through visualization and descriptive statistics.
Furthermore, it is necessary to preprocess the data appropriately so you can use it for model training.

1. Load the chosen dataset and import the necessary libraries. The choice of libraries is up to you.
2. Introduce the individual features with text descriptions.
3. Analyze the dataset using descriptive statistics with appropriate visualization methods. Comment on your findings.
4. Investigate missing values (including their representation) and outliers. Again, use visualizations if possible and
   comment on your findings.
5. Make all other necessary adjustments for working with the chosen dataset (e.g., data type conversions, removal of
   duplicate records, creation of new features, unification of missing data representation, or their removal, etc.). You
   can return to modifying the dataset during the task.
6. Prepare the dataset for training and evaluating the chosen model (e.g., appropriately split the data if necessary for
   your model and evaluation, comment on the split, or use cross-validation, etc., known from BI-ML1).

You can earn up to 7 points from this section.

**⚙️ Model:**
In this section, your task is to train a model that will attempt to solve your task. Focus primarily on the
visualization of individual steps and results, including comments. The quality of the model itself will not be
evaluated.

1. Choose an appropriate classification/regression model for your task.
2. Select at least two hyperparameters with at least five values (this can be more or less depending on the chosen
   hyperparameter) whose best combination you will search for during model training. Describe the chosen hyperparameters
   and their values.
3. Choose and describe the loss function you will use to evaluate the success of the model.
4. Train the model on the dataset. If possible, visualize the model.
5. Appropriately visualize and comment on the impact of individual hyperparameter combinations on the model's success.
   State the best combination.
6. If possible (!), visualize the decision boundary of the model for the features you selected (e.g., only for 2). If
   not possible, justify or implement another visualization related to presenting the best model.
7. Appropriately visualize the success of the final model - use at least two visualization methods.

**For enthusiasts:** If you want, you can use multiple models for solving the task and compare them (including tuning
hyperparameters and other steps mentioned above).

You can earn up to 18 points from this section.

### Scoring

Summary of points you can earn:

- 5 points for continuous comments and visual presentation of the process and results,
- 7 points for data preprocessing and presentation,
- 18 points for training and evaluating the model.

In total, you can earn a maximum of 30 points for Homework Assignment No. 3 (each team member or individual).

