#pragma once

class IndexBuffer{
private:
  unsigned int m_RendererID;
  unsigned int m_Count;
public:
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer();
 
  void Bind() const;
  void Unbind() const;

  // sert a indiquer au compilateur de remplacer directement dans le code binaire
  // final l'appel de cette fonction par son contenu. Ca evite de faire un saut de memoire
  // et donc un peu plus performant.
  inline unsigned int GetCount() const {return m_Count;}
};
