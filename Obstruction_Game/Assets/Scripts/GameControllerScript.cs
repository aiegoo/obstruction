using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameControllerScript : MonoBehaviour
{

    public GameObject gridSpace;
    public GameObject canvas;
    public int rows;
    public int columns;

    public void Awake() {

        int canvasX = (int)canvas.transform.position.x;
        int canvasY = (int)canvas.transform.position.y;
        int multiplier = 170;
        for (int y = rows; y >= -rows; y--) {
            for (int x = -columns; x <= columns; x++) {
                Instantiate(gridSpace, new Vector3(canvasX + x * multiplier, canvasY + y * multiplier, 0), Quaternion.identity, canvas.transform);
            }
        }
    }

    public void restart() {

        SceneManager.LoadScene(0);
    }

}
