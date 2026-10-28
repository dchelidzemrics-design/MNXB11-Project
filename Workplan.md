# Workplan for MNXB11 project

Team number: 8

Team members: David Chelidze, Estrella González Gómez, Joel Johansen, Maja Solman Wålsten and Evelina Vedin Meijer. 

# Workflow chart

```mermaid 
%%{init: { 'theme':'neutral', 'fontSize': '11px'} }%%
flowchart TD
    %% This will be the same for all analyses
    A["datasets/datasets.tgz"] --> B("Clean <br> (bash)")
    B --> C["datasets/Data.csv"]
    C --> D("Extract and reformat <br> (c++)")
    D --> E["Lund.root"]

    %% The seperate analyses
    E --> F("Analysis 1 <br> (the start, end and duration of summer each year)")
    E --> G("Analysis 2 <br> (days above threshold temperature during fixed time interval)")
    E --> H("Analysis 3 <br> (the temperature for every day of the year)")
    E --> I("Analysis 4 <br> (Distribution of warmest and coldest days of the year)")

    %% Analysis 1 workflow
    F --> F1["summer_start_end_duration.root"]
    F1 --> F2("Write ROOT macro that plots the start, end and duration of summer against the year")
    F2 --> F3("summer_start.pdf <br> summer_end.pdf <br> summer_duration.pdf")
    
    %% Analysis 2 workflow
    G --> G1["Analysis2.root"]
    G1 --> G2("Analysis 2 root macro")
    G2 --> G3("Analysis2.pdf")

    %% Analysis 3 workflow
    H --> H1["Analysis3.root"]
    H1 --> H2("Analysis 3 root macro")
    H2 --> H3("Analysis3.pdf")

    %% Analysis 4 workflow
    I --> I1["Analysis4.root"]
    I1 --> I2("Analysis 4 root macro")
    I2 --> I3("Analysis4.pdf")

    %% Legend 
    subgraph Legend ["Legend"]
        direction LR
        L1["Files"] ~~~ L2("Tasks")
    end

    %% Seperate Files and Tasks into different classes
    %% with different colors
    classDef Files fill:#90bd82;
    classDef Tasks fill:#b9a1ed;

    class L1,A,C,E,F1,F3,G1,G3,H1,H3,I1,I3,J1,J3 Files;
    class L2,B,D,F,G,H,I,J,F2,G2,H2,I2,J2 Tasks;
```
