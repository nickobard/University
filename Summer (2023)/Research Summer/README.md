# Research Summer - Keyword Matching

In this summer research project, the focus was on developing and evaluating advanced keyword matching techniques to enhance named entity recognition (NER) in natural language processing (NLP). Traditional keyword matching relies on predefined lists of related keywords for each entity category, which can be limiting when dealing with phrases or variations like abbreviations.

## Formal Assignment:

Keyword matching is a simple but powerful named entity recognition technique in natural language text, which can be used by itself, or to support systems based on deep learning models. With this approach, for each named entity category (e.g. “bacteria”), a list of related keywords (e.g. “Salmonella”, “Streptococcus”) is provided, which is then used for the matching of words in query texts.

This topic focuses on the research and development of advanced keyword-matching techniques, such as phrase matching (e.g. ”Escherichia coli”) or fuzzy matching (e.g. ”E. coli”). Numerous approaches can be investigated, such as similarity-based methods (e.g. edit distance, word embeddings, or phrase embeddings), or techniques used in the related problem of word alignment [1]. These approaches will be qualitatively compared. An important factor is computational efficiency, as the number of candidate phrases explodes with longer texts.

## Results:

### Dataset Preparation:

- Created small custom dataset (dataset_1.json) to suit specific evaluation needs.

### Embedding Models and Tools:

- Gensim Word2Vec:
  - Loaded pre-trained models like word2vec-google-news-300.
  - Evaluated word similarities using different similarity functions (cosine, Euclidean distance, etc.).
- Flair Embeddings:
  - Used TransformerWordEmbeddings with models like bert-base-uncased.
  - Experimented with parameters:
    - Layers: all layers vs. last layer.
    - Context: with sentence context vs. without.
    - Subtoken pooling strategies.
- Transformers Library (Hugging Face):
  - Employed BERT models to extract embeddings.
  - Tested aggregating over all layers vs. the last layer.

### Evaluation and Analysis:

- Implemented evaluators for each embedding approach to standardize evaluations.
- Calculated statistical metrics and generated precision-recall curves.
- Analyzed out-of-vocabulary (OOV) words and words lost during processing.
- Compared the impact of different similarity functions and embedding configurations on performance.

### Utilities and Visualization:

- Developed utility scripts for preprocessing, similarity calculations, and statistical analysis.
- Created visualization tools for highlighting results, plotting graphs, and presenting data in tables.

***

The project systematically compared various state-of-the-art keyword matching techniques using advanced embedding models like Word2Vec, BERT, and Flair embeddings. By experimenting with different configurations—such as layer selections, context usage, and similarity measures—the research provided some insights into the effectiveness of these techniques for named entity recognition.

### Code Structure:

    excluding: "__init__.py"

```text
.
├── environment.yml
├── README.md
├── scripts
│   ├── create_or_update_mamba_env.sh
│   └── mamba_update_environment_file.sh
└── src
    ├── datasets
    │   ├── dataset_1.json
    │   ├── MEN
    │   │   ├── MEN_dataset_lemma_form_full
    │   │   └── MEN_dataset_natural_form_full
    │   └── SimLex
    │       ├── README.txt
    │       └── SimLex-999.txt
    └── embeddings
        ├── 1.1_gensim_w2v.ipynb
        ├── 2.1_flair_bert_all_layers.ipynb
        ├── 2.2_flair_bert_last_layer.ipynb
        ├── 2.3_flair_bert_all_layers_no_sent_context.ipynb
        ├── 2.4_flair_bert_last_layers_no_sent_context.ipynb
        ├── 3.1_transformers_bert.ipynb
        ├── 3.2_transformers_bert_all_layers.ipynb
        ├── 4.1_flair_stacked.ipynb
        ├── bert
        │   ├── 1_bert_on_MEN_dataset.ipynb
        │   └── 2_bert_extracting_embeddings.ipynb
        ├── dataset_creation_helper.ipynb
        ├── evaluators
        │   ├── base.py
        │   ├── flair_evaluator.py
        │   ├── gensim_evaluator.py
        │   └── transformers_evaluator.py
        ├── gensim_corpora.ipynb
        ├── schemes
        │   └── dataset.py
        ├── testing_utils.ipynb
        ├── utils
        │   ├── preprocessing.py
        │   ├── smilarity.py
        │   ├── statistics.py
        │   └── visualization
        │       ├── graphs.py
        │       ├── highligter.py
        │       └── table_view.py
        └── word2vec
            ├── 1_algorithm.ipynb
            ├── 2_statistics.ipynb
            ├── 3_men_dataset_w2w.ipynb
            ├── 4_simlex_dataset_w2v.ipynb
            ├── 5_men_dataset_dot_product.ipynb
            ├── 6_men_dataset_euclid_dist.ipynb
            ├── aglorithm.py
            └── models.ipynb

```