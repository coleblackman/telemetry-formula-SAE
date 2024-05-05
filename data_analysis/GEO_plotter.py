import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import geopandas as gpd
import contextily as ctx

def GEO_plot(data, title):
    """
    Plot the geospatial data with CRC errors and satellite imagery background.
    :param data: DataFrame containing the geospatial data.
    :param title: Title of the plot.
    """
    # Ensure "RSSI", "Latitude", and "Longitude" are treated as strings for proper comparison
    data["RSSI"] = data["RSSI"].astype(str)
    data["Latitude"] = data["Latitude"].astype(str)
    data["Longitude"] = data["Longitude"].astype(str)

    # Prepare data
    parsed_data = []

    for index, row in data.iterrows():
        if "CRC error!" in row["RSSI"]:
            # Mark CRC error
            parsed_data.append([np.nan, np.nan, True])
        else:
            # Extract Latitude and Longitude
            latitude = float(row["Latitude"])
            longitude = float(row["Longitude"])
            parsed_data.append([latitude, longitude, False])

    # Convert to DataFrame
    df = pd.DataFrame(parsed_data, columns=["Latitude", "Longitude", "CRC_Error"])

    # Convert to a GeoDataFrame
    gdf = gpd.GeoDataFrame(df, geometry=gpd.points_from_xy(df.Longitude, df.Latitude))

    # Define the coordinate reference system (CRS)
    gdf = gdf.set_crs(epsg=4326)  # WGS84
    gdf = gdf.to_crs(epsg=3857)  # Web Mercator for OSM compatibility

    # Plot with a background map
    fig, ax = plt.subplots(figsize=(10, 6))
    gdf[~gdf["CRC_Error"]].plot(ax=ax, marker='o', color='red', label='Location', zorder=3)
    gdf[gdf["CRC_Error"]].plot(ax=ax, marker='o', color='red', label='CRC Error', zorder=4)

    # Calculate the bounds of the points to zoom out
    x_min, y_min, x_max, y_max = gdf.total_bounds
    x_buffer = (x_max - x_min) * 0.5  # Expand horizontally by a factor of 1.5
    y_buffer = (y_max - y_min) * 0.5  # Expand vertically by a factor of 1.5
    ax.set_xlim(x_min - x_buffer, x_max + x_buffer)
    ax.set_ylim(y_min - y_buffer, y_max + y_buffer)

    # Add satellite basemap
    ctx.add_basemap(ax, source=ctx.providers.Esri.WorldImagery)

    ax.set_xlabel("Longitude")
    ax.set_ylabel("Latitude")
    ax.set_title(title)
    plt.legend()
    plt.grid(visible=True)
    plt.savefig(f"{title}.png")
    plt.close()

# List of CSV filenames to be processed
csv_filenames = [
    "SAE_RUN_1_CLOSE_SF_8.csv",
    "SAE_RUN_2_SF_8.csv",
    "SAE_RUN_3_SF_8_BEHIND_CHURCH.csv",
    "SAE_RUN_6_SF_9_BIG_ANTENNA_SCHOOLCONTINUINTSTUDIES.csv",
    "SAE_RUN_8_BIG_ANTENNA_SF_9_EDGEMONT.csv",
    "RUN_7_SF_9_BIG_ANTENNA_PHYSICS_AND_OLDDORMS.csv"
]

# Process each CSV file
for filename in csv_filenames:
    # Read data from the CSV file
    df_raw = pd.read_csv(filename).rename(columns=lambda x: x.strip())

    # Generate the title for the plot
    title = filename.replace(".csv", "")

    # Call the plotting function
    GEO_plot(df_raw, title)
