# Workplan for MNXB11 project

Team number: 8

Team members: David Chelidze, Estrella González Gómez, Joel Johansen, Maja Solman Wålsten and Evelina Vedin Meijer. 

# Workflow chart

```mermaid 
%%{init: { 'theme':'neutral', 'fontSize': '11px'} }%%
flowchart TD
    %% This will be the same for all analyses
    A["datasets/datasets.tgz"] --> B("Parse raw data <br> (BASH)")
    B --> C["datasets/parseddata.csv"]
    C --> D("Extract and reformat <br> (c++, ROOT)")
    D --> E["temperature_tree.root"]

    %% The seperate analyses
    E --> G("Analysis 1 <br> (Days above threshold temperature during fixed time interval)")
    E --> H("Analysis 2 <br> (The temperature for every day of the year)")
    E --> I("Analysis 3 <br> (Distribution of warmest and coldest days of the year)")
    E --> J("Analysis 4 <br> ")

    %% Analysis 1 workflow
    G --> G1["Analysis1.root"]
    G1 --> G2("Analysis 1 root macro")
    G2 --> G3("Analysis1.pdf")

    %% Analysis 2 workflow
    H --> H1["Analysis2.root"]
    H1 --> H2("Analysis 2 root macro")
    H2 --> H3("Analysis2.pdf")

    %% Analysis 3 workflow
    I --> I1["Analysis3.root"]
    I1 --> I2("Analysis 3 root macro")
    I2 --> I3("Analysis3.pdf")

    %% Analysis 4 workflow
    J --> J1["Analysis4.root"]
    J1 --> J2("Analysis 4 root macro")
    J2 --> J3("Analysis4.pdf")

    %% Legend 
    subgraph Legend ["Legend"]
        direction LR
        L1["Files"] ~~~ L2("Tasks")
    end

    %% Seperate Files and Tasks into different classes
    %% with different colors
    classDef Files fill:#90bd82;
    classDef Tasks fill:#b9a1ed;

    class L1,A,C,E,G1,G3,H1,H3,I1,I3,J1,J3 Files;
    class L2,B,D,G,H,I,J,F,F2,G2,H2,I2,J2 Tasks;
```
